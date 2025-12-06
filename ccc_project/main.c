#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[20];
char currentUser[50];

/* Function Declarations */
int loginSystem();
void mainMenu();
void adminMenu();
void userMenu();
void staffMenu();
void guestMenu();

/* CRUD */
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

/* NEW FEATURE */
void classStats();

/* ================= MAIN =================== */
int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nAccess Denied. Exiting...\n");
    }
    return 0;
}


/* ================= LOGIN =================== */
int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[20];

    printf("===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s",
                  fileUser, filePass, fileRole) == 3)
    {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0)
        {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


/* ================= MAIN MENU =================== */
void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else
        guestMenu();
}


/* ================= ADMIN MENU =================== */
void adminMenu() {
    int choice;

    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("7. Class Statistics (Avg, Topper, Lowest)\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            case 7: classStats(); break;
            default: printf("Invalid choice!\n");
        }

    } while (1);
}


/* ================= USER MENU =================== */
void userMenu() {
    int choice;

    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;
            default: printf("Invalid!\n");
        }

    } while (1);
}


/* ================= STAFF MENU =================== */
void staffMenu() {
    int choice;

    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Logout\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: return;
            default: printf("Invalid!\n");
        }

    } while (1);
}


/* ================= GUEST MENU =================== */
void guestMenu() {
    int choice;

    do {
        printf("\n===== GUEST MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Logout\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: return;
            default: printf("Invalid!\n");
        }

    } while (1);
}


/* ================= CRUD FUNCTIONS =================== */

void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter Roll: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n",
            s.roll, s.name, s.marks);

    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("No student file found!\n");
        return;
    }

    printf("\n--- STUDENT LIST ---\n");

    while (fscanf(fp, "%d %s %f",
                  &s.roll, s.name, &s.marks) == 3)
    {
        printf("Roll: %d | Name: %s | Marks: %.2f\n",
               s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int roll, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");

    printf("Enter Roll To Search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f",
                  &s.roll, s.name, &s.marks) == 3)
    {
        if (s.roll == roll) {
            printf("\nFOUND: %d %s %.2f\n",
                   s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Student Not Found!\n");
}

void updateStudent() {
    struct Student s;
    int roll, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Roll To Update: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f",
                  &s.roll, s.name, &s.marks) == 3)
    {
        if (s.roll == roll) {
            found = 1;
            printf("New Name: ");
            scanf("%s", s.name);

            printf("New Marks: ");
            scanf("%f", &s.marks);
        }

        fprintf(temp, "%d %s %.2f\n",
                s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Student Updated!\n");
    else
        printf("Student Not Found!\n");
}

void deleteStudent() {
    struct Student s;
    int roll, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Roll To Delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f",
                  &s.roll, s.name, &s.marks) == 3)
    {
        if (s.roll != roll)
            fprintf(temp, "%d %s %.2f\n",
                    s.roll, s.name, s.marks);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Student Deleted!\n");
    else
        printf("Student Not Found!\n");
}


/* ================= CLASS STATS FEATURE =================== */

void classStats() {

    struct Student s, top, low;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("Student file missing!\n");
        return;
    }

    float total = 0;
    int count = 0;

    while (fscanf(fp,"%d %s %f",
                  &s.roll, s.name, &s.marks) == 3)
    {
        total += s.marks;

        if (count == 0) {
            top = s;
            low = s;
        }

        if (s.marks > top.marks)
            top = s;

        if (s.marks < low.marks)
            low = s;

        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("No students found!\n");
        return;
    }

    printf("\n===== CLASS STATISTICS =====\n");
    printf("Total Students: %d\n", count);
    printf("Class Average: %.2f\n", total / count);

    printf("\n--- TOPPER ---\n");
    printf("Roll : %d\n", top.roll);
    printf("Name : %s\n", top.name);
    printf("Marks: %.2f\n", top.marks);

    printf("\n--- LOWEST SCORER ---\n");
    printf("Roll : %d\n", low.roll);
    printf("Name : %s\n", low.name);
    printf("Marks: %.2f\n", low.marks);
}
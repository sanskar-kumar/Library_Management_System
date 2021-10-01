#include <stdio.h>
#include <stdlib.h>
typedef struct student
{
    int bookno;
    char name[20];
    char authorname[20];
    struct date
    {
        int day;
        int month;
        int year;
    } datee[2];

} student;
void create()
{
    student *s;
    FILE *fp;
    int n, i, j;
    printf("Enter no. of entries you want:");
    scanf("%d", &n);
    s = (student *)calloc(n, sizeof(student));
    fp = fopen("library.txt", "w");

    for (int i = 0; i < n; i++)
    {
        printf("Enter Book No.: ");
        scanf("%d", &s[i]);
        fflush(stdin);
        printf("\nEnter Book Name:");
        gets(s[i].name);
        fflush(stdin);
        printf("Enter Book Author:");
        gets(s[i].authorname);
        fflush(stdin);
        printf("Enter date of issue in DD MM YYYY format: ");
        scanf("%d %d %d", &s[i].datee->day, &s[i].datee->month, &s[i].datee->year);
        fwrite(&s[i], sizeof(student), 1, fp);
    }
    fclose(fp);
}
void display()
{
    student s1;
    FILE *fp;
    fp = fopen("library.txt", "r");
    printf("\n\n\t **** Students Details Are As Follows ****\n");
    printf("-------------------------------------------------------------------");
    printf("\nBook.No\tBook Name\t\tBook Author\tDate Issued\n\n");
    printf("-------------------------------------------------------------------");
    while (fread(&s1, sizeof(student), 1, fp))
    {
        printf("\n%d\t%s\t\t", s1.bookno, s1.name);
        printf("%s\t\t ", s1.authorname);
        printf("%d/%d/%d", s1.datee->day, s1.datee->month, s1.datee->year);
    }
    fclose(fp);
}
void append()
{
    student *s;
    FILE *fp;
    int n, i, j;
    printf("Enter no. of entries you want:");
    scanf("%d", &n);
    s = (student *)calloc(n, sizeof(student));
    fp = fopen("library.txt", "a");

    for (int i = 0; i < n; i++)
    {
        printf("Enter Book No.: ");
        scanf("%d", &s[i]);
        fflush(stdin);
        printf("\nEnter Book Name:");
        gets(s[i].name);
        fflush(stdin);
        printf("Enter Book Author:");
        gets(s[i].authorname);
        fflush(stdin);
        printf("Enter date of issue in DD MM YYYY format: ");
        scanf("%d %d %d", &s[i].datee->day, &s[i].datee->month, &s[i].datee->year);
        fwrite(&s[i], sizeof(student), 1, fp);
    }
    fclose(fp);
}
void search()
{
    student s1;
    FILE *fp;
    int bno, found = 0;
    fp = fopen("library.txt", "r");
    printf("Enter Book No. to search:");
    scanf("%d", &bno);
    printf("\n\n\t **** Students Details Are As Follows ****\n");
    printf("-------------------------------------------------------------------");
    printf("\nBook.No\tBook Name\t\tBook Author\tDate Issued\n\n");
    printf("-------------------------------------------------------------------");
    while (fread(&s1, sizeof(student), 1, fp))
    {
        if (s1.bookno == bno)
        {
            found = 1;
            printf("\n%d\t%s\t\t", s1.bookno, s1.name);
            printf("%s\t\t ", s1.authorname);
            printf("%d/%d/%d", s1.datee->day, s1.datee->month, s1.datee->year);
        }
    }
    if (!found)
    {
        printf("\nBook Record Not Found\n");
    }

    fclose(fp);
}
void delete ()
{
    student s1;
    FILE *fp, *fp1;
    int bno, found = 0;
    fp = fopen("library.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Enter Book No. to Delete:");
    scanf("%d", &bno);
    while (fread(&s1, sizeof(student), 1, fp))
    {
        if (s1.bookno == bno)
        {
            found = 1;
        }
        else
            fwrite(&s1, sizeof(student), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    if (found)
    {
        fp = fopen("library.txt", "w");
        fp1 = fopen("temp.txt", "r");
        while (fread(&s1, sizeof(student), 1, fp1))
        {
            fwrite(&s1, sizeof(student), 1, fp);
        }
    }

    fclose(fp);
}
void fee()
{
    student s1;
    FILE *fp;
    int bn, fond = 0, d, m, y, dd, mm, yy, a, b, c, ans = 0;
    printf("Enter the Book No. on which fine is to be calculated : ");
    scanf("%d", &bn);
    fp = fopen("library.txt", "r");
    while (fread(&s1, sizeof(student), 1, fp))
    {
        if (bn == s1.bookno)
        {
            fond = 1;
            d = s1.datee->day;
            m = s1.datee->month;
            y = s1.datee->year;
            break;
        }
    }
    printf("Enter check out day: ");
    scanf("%d", &dd);
    printf("Enter check out month: ");
    scanf("%d", &mm);
    printf("Enter check out year: ");
    scanf("%d", &yy);
    if (mm > m)
    {
        c = yy - y;
    }
    else if (mm < m)
    {
        c = yy - y;
        --c;
    }
    else
    {
        if (dd > d)
        {
            c = yy - y;
        }
        else
        {
            c = yy - y;
            c--;
        }
    }

    if (dd >= d)
    {
        b = mm - m;
        if (b < 0)
        {
            b += 12;
        }
    }
    else
    {
        b = mm - m;
        b += 12;
    }
    if (dd >= d)
    {
        a = dd - d;
    }
    else
    {
        a = dd - d;
        a += 30;
    }
    ans += a;
    ans += (b * 30);
    ans += (c * 365);
    printf("\nFINE CHARGE(Imposed(@Rs10/day) if book is not submitted within 30 days of issue) : ");
    if (ans <= 30)
    {
        printf("0\n");
    }
    else
    {
        ans = ans - 30;
        ans *= 10;
        printf("%d\n", ans);
    }
}
int main()
{
    int choice;
    while (choice != 7)

    {
        printf("\t***********************************************\n");
        printf("\t\tWELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
        printf("\t***********************************************\n\n\n");

        printf("Issued book should be submitted or renewed within 30 days of issue\n");

        printf("\t**** AVAILABLE FUNCTIONALITIES ****\n\n\n");
        printf("\t\t1: Insert book record\n");
        printf("\t\t2: Display book record\n");
        printf("\t\t3: Add book record\n");
        printf("\t\t4: Search book record\n");
        printf("\t\t5: Delete book record\n");
        printf("\t\t6: Calculate fine\n");
        printf("\t\t7: Exit\n\n");
        printf("\t\tEnter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create();
            break;
        case 2:
            display();
            break;
        case 3:
            append();
            break;
        case 4:
            search();
            break;
        case 5:
            delete ();
            break;
        case 6:
            fee();
            break;
        case 7:
            exit(1);
        default:
            printf("\n\t\tWrong choice Entered");
        }
        printf("\n\t\tPress any key to continue\n");
        getch();
    }

    return 0;
}

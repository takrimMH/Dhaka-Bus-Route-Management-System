#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUSES 50
#define MAX_ROUTE 2000
#define MAX_STOPS 300
#define MIN_FARE 10
#define roundUp5(x) (((int)(x) % 5 == 0) ? (int)(x) : ((int)(x) / 5 + 1) * 5)
typedef struct
{
    char name[100];
    char start[100];
    char end[100];
    char route[MAX_ROUTE];
    float rawFare;
} Bus;
void toLower(char *s)
{
    for (; *s; s++)
        if (*s >= 'A' && *s <= 'Z')
            *s += 32;
}
int stopPos(char *route, char *stop)
{
    char r[MAX_ROUTE], s[100];
    strcpy(r, route);
    strcpy(s, stop);
    toLower(r);
    toLower(s);

    int pos = 0;
    for (char *t = strtok(r, "->"); t; t = strtok(NULL, "->"), pos++)
        if (strcmp(t, s) == 0)
            return pos;
    return -1;
}
void printRoute(char *route)
{
    char r[MAX_ROUTE];
    strcpy(r, route);
    int first = 1;
    for (char *t = strtok(r, "->"); t; t = strtok(NULL, "->"))
    {
        if (!first)
            printf(" <-> ");
        printf("%s", t);
        first = 0;
    }
    printf("\n");
}

void printSegment(char *route, int src, int dst)
{
    char *stops[MAX_STOPS];
    char r[MAX_ROUTE];
    strcpy(r, route);
    int n = 0;
    for (char *t = strtok(r, "->"); t; t = strtok(NULL, "->"))
        stops[n++] = t; /* points into r — valid here */
    int lo = src < dst ? src : dst;
    int hi = src < dst ? dst : src;
    if (src <= dst)
        for (int i = lo; i <= hi; i++)
        {
            if (i > lo)
                printf(" <-> ");
            printf("%s", stops[i]);
        }
    else
        for (int i = hi; i >= lo; i--)
        {
            if (i < hi)
                printf(" <-> ");
            printf("%s", stops[i]);
        }
    printf("\n");
}
void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
int countStops(char *route)
{
    char r[MAX_ROUTE];
    strcpy(r, route);
    int n = 0;
    for (char *t = strtok(r, "->"); t; t = strtok(NULL, "->"))
        n++;
    return n;
}
void printFares(float rawFare, int srcPos, int dstPos, int totalStops)
{
    int segments = srcPos > dstPos ? srcPos - dstPos : dstPos - srcPos;
    float partial = rawFare * segments / (float)(totalStops - 1);
    int reg = roundUp5(partial);
    int stu = roundUp5(partial / 2.0f);
    if (reg < MIN_FARE)
        reg = MIN_FARE;
    if (stu < MIN_FARE)
        stu = MIN_FARE;
    printf("  Regular Fare : %d BDT\n", reg);
    printf("  Student Fare : %d BDT\n", stu);
}
void loadBuses(Bus *b, int *n)
{
    int i = 0;
    strcpy(b[i].name, "Raida");
    strcpy(b[i].start, "Postogola");
    strcpy(b[i].end, "Dia Bari");
    strcpy(b[i].route, "Postogola->Dholairpar->Jatrabari->Janapath Moor->Sayedabad->Mugdapara->Bashabo->Khilgaon->Malibagh Railgate->Rampura Bazar->Rampura Bridge->Merul Badda->Badda->Uttar Badda->Bashtola->Notun Bazar->Nadda->Bashundhara->Jamuna Future Park->Kuril Chourasta->Kuril Bishwa Road->Khilkhet->Airport->Jashimuddin->Rajlakshmi->Azampur->House Building->Dia Bari");
    b[i++].rawFare = 64.0;
    strcpy(b[i].name, "BRTC");
    strcpy(b[i].start, "Motijheel");
    strcpy(b[i].end, "Gabtoli");
    strcpy(b[i].route, "Motijheel->Gulistan->GPO->Paltan->Press Club->High Court->Matsya Bhaban->Shahbag->Bangla Motor->Kawran Bazar->Farmgate->Khamar Bari->Asad Gate->College Gate->Shishu Mela->Shyamoli->Kallyanpur->Technical->Gabtoli");
    b[i++].rawFare = 46.0;
    strcpy(b[i].name, "Welcome");
    strcpy(b[i].start, "Nandan Park");
    strcpy(b[i].end, "Motijheel");
    strcpy(b[i].route, "Nandan Park->Zirani Bazar->Baipayl->Nobinagar->Savar->Hemayetpur->Amin Bazar->Gabtoli->Technical->Kallyanpur->Shyamoli->Shishu Mela->College Gate->Asad Gate->Khamar Bari->Farmgate->Kawran Bazar->Bangla Motor->Shahbag->High Court->Press Club->Paltan->GPO->Gulistan->Motijheel");
    b[i++].rawFare = 90.0;
    strcpy(b[i].name, "VIP 27");
    strcpy(b[i].start, "Azimpur");
    strcpy(b[i].end, "Abdullahpur");
    strcpy(b[i].route, "Azimpur->Nilkhet->New Market->City College->Kalabagan->Banani->Kakali->MES->Shewra->Kuril Bishwa Road->Khilkhet->Airport->Jashimuddin->Rajlakshmi->Azampur->House Building->Abdullahpur");
    b[i++].rawFare = 52.0;
    strcpy(b[i].name, "Victor Classic");
    strcpy(b[i].start, "Sadarghat");
    strcpy(b[i].end, "Kuril Bishwa Road");
    strcpy(b[i].route, "Sadarghat->Ray Saheb Bazar->Naya Bazar->Golap Shah Mazar->GPO->Paltan->Kakrail->Shantinagar->Malibaag Moor->Mouchak->Malibagh Railgate->Hazipara->Rampura Bazar->Rampura Bridge->Merul Badda->Badda->Shahjadpur->Bashtola->Notun Bazar->Nadda->Bashundhara->Jamuna Future Park->Kuril Bishwa Road");
    b[i++].rawFare = 38.0;
    strcpy(b[i].name, "Turag");
    strcpy(b[i].start, "Jatrabari");
    strcpy(b[i].end, "Abdullahpur");
    strcpy(b[i].route, "Jatrabari->Sayapabad->Mugdapara->Bashabo->Khilgaon->Malibaag Moor->Rampura Bazar->Rampura Bridge->Merul Badda->Badda->Uttar Badda->Bashtola->Notun Bazar->Nadda->Bashundhara->Jamuna Future Park->Kuril Bishwa Road->Khilkhet->Airport->Jashimuddin->Rajlakshmi->Azampur->House Building->Abdullahpur");
    b[i++].rawFare = 46.0;
    strcpy(b[i].name, "Bashumoti");
    strcpy(b[i].start, "Gazipur Chourasta");
    strcpy(b[i].end, "Gabtoli");
    strcpy(b[i].route, "Gazipur Chourasta->Tongi->Airport->Khilkhet->Kalshi->Pallabi->Mirpur 11->Mirpur 10->Mirpur 1->Gabtoli");
    b[i++].rawFare = 65.0;
    strcpy(b[i].name, "Balaka");
    strcpy(b[i].start, "Sayapabad");
    strcpy(b[i].end, "Abdullahpur");
    strcpy(b[i].route, "Sayapabad->Manik Nagar->TT Para->Kamalapur->Malibaag Moor->Mouchak->Mogbazar->Sat Rasta->Nabisco->Mohakhali->Chairman Bari->Banani->Kakali->Staff Road->MES->Shewra->Kuril Bishwa Road->Khilkhet->Airport->Jashimuddin->Rajlakshmi->Azampur->House Building->Abdullahpur");
    b[i++].rawFare = 52.0;
    strcpy(b[i].name, "Akash");
    strcpy(b[i].start, "Kadamtali");
    strcpy(b[i].end, "Abdullahpur");
    strcpy(b[i].route, "Kadamtali->Keraniganj->Babubazar->Naya Bazar->Golap Shah Mazar->GPO->Paltan->Kakrail->Shantinagar->Malibagh->Mouchak->Malibagh Railgate->Hazipara->Rampura Bazar->Merul Badda->Badda->Shahjadpur->Bashtola->Notun Bazar->Nadda->Bashundhara->Jamuna Future Park->Kuril Bishwa Road->Khilkhet->Airport->Jashimuddin->Rajlakshmi->Azampur->House Building->Abdullahpur");
    b[i++].rawFare = 64.0;
    *n = i;
}
void menu()
{
    printf("\n========================================\n");
    printf("=>  DHAKA BUS ROUTE MANAGEMENT SYSTEM  <=\n");
    printf("========================================\n");
    printf("1. Search Bus by Source and Destination\n");
    printf("2. Show All Bus Routes\n");
    printf("3. Show Route Details of a Bus\n");
    printf("4. Exit\n");
    printf("========================================\n");
}
void searchRoutes(Bus *b, int n, char *src, char *dst)
{
    char s[100], d[100];
    strcpy(s, src);
    strcpy(d, dst);
    toLower(s);
    toLower(d);
    printf("\n========================================\n");
    printf("From : %s  |  To : %s\n", src, dst);
    printf("========================================\n");
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        int sp = stopPos(b[i].route, s);
        int dp = stopPos(b[i].route, d);
        if (sp == -1 || dp == -1)
            continue;

        printf("\n  Bus   : %s\n  Route : ", b[i].name);
        printSegment(b[i].route, sp, dp);
        printFares(b[i].rawFare, sp, dp, countStops(b[i].route));
        printf("----------------------------------------\n");
        found = 1;
    }

    if (!found)
    {
        printf("No bus found. Check spelling and try again.\n");
        printf("Tip: Use option 2 to see all stop names.\n");
    }
}
void showAllRoutes(Bus *b, int n)
{
    printf("\n========================================\n");
    printf("  ALL BUS ROUTES  [<->] both directions \n");
    printf("========================================\n");
    for (int i = 0; i < n; i++)
    {
        int total = countStops(b[i].route);
        printf("\n[%d] %s  (%s <-> %s)\n    ", i + 1, b[i].name, b[i].start, b[i].end);
        printRoute(b[i].route);
        printf("    ");
        printFares(b[i].rawFare, 0, total - 1, total);
        printf("----------------------------------------\n");
    }
}
void showBusDetails(Bus *b, int n, char *name)
{
    char search[100], temp[100];
    strcpy(search, name);
    toLower(search);

    for (int i = 0; i < n; i++)
    {
        strcpy(temp, b[i].name);
        toLower(temp);
        if (strcmp(temp, search) != 0)
            continue;

        printf("\n========================================\n");
        printf("  %s  (%s <-> %s)\n", b[i].name, b[i].start, b[i].end);
        int total = countStops(b[i].route);
        printFares(b[i].rawFare, 0, total - 1, total);
        printf("========================================\n  ");
        printRoute(b[i].route);
        return;
    }

    printf("Bus '%s' not found.\nAvailable: ", name);
    for (int i = 0; i < n; i++)
        printf("%s%s", b[i].name, i < n - 1 ? ", " : "\n");
}
int main()
{
    Bus buses[MAX_BUSES];
    int count = 0;
    loadBuses(buses, &count);
    int choice;
    char src[100], dst[100], name[100];
    do
    {
        menu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInput();
        switch (choice)
        {
        case 1:
            printf("Starting Location : ");
            fgets(src, sizeof(src), stdin);
            src[strcspn(src, "\n")] = 0;
            printf("Destination       : ");
            fgets(dst, sizeof(dst), stdin);
            dst[strcspn(dst, "\n")] = 0;
            searchRoutes(buses, count, src, dst);
            break;
        case 2:
            showAllRoutes(buses, count);
            break;
        case 3:
            printf("Bus Name : ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            showBusDetails(buses, count, name);
            break;
        case 4:
            printf("Thank you for using Dhaka Bus Service!\n");
            break;
        default:
            printf("Invalid choice. Enter 1-4.\n");
        }
    } while (choice != 4);
    return 0;
}

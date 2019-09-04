#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ULONG ;
typedef  int UCHAR ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _strnicmp (char*,char*,int) ; 
 void* atoi (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

BOOLEAN DissectArcPath(CHAR *ArcPath, CHAR *BootPath, UCHAR* BootDrive, ULONG* BootPartition)
{
    char *p;

    /* Detect ramdisk path */
    if (_strnicmp(ArcPath, "ramdisk(0)", 10) == 0)
    {
        /* Magic value for ramdisks */
        *BootDrive = 0x49;
        *BootPartition = 1;

        /* Get the path */
        p = ArcPath + 11;
        strcpy(BootPath, p);
        return TRUE;
    }

    if (_strnicmp(ArcPath, "multi(0)disk(0)", 15) != 0)
        return FALSE;

    p = ArcPath + 15;
    if (_strnicmp(p, "fdisk(", 6) == 0)
    {
        /*
         * Floppy disk path:
         *  multi(0)disk(0)fdisk(x)\path
         */
        p = p + 6;
        *BootDrive = atoi(p);
        p = strchr(p, ')');
        if (p == NULL)
            return FALSE;
        p++;
        *BootPartition = 0;
    }
    else if (_strnicmp(p, "cdrom(", 6) == 0)
    {
        /*
         * Cdrom path:
         *  multi(0)disk(0)cdrom(x)\path
         */
        p = p + 6;
        *BootDrive = atoi(p) + 0x80;
        p = strchr(p, ')');
        if (p == NULL)
            return FALSE;
        p++;
        *BootPartition = 0xff;
    }
    else if (_strnicmp(p, "rdisk(", 6) == 0)
    {
        /*
         * Hard disk path:
         *  multi(0)disk(0)rdisk(x)partition(y)\path
         */
        p = p + 6;
        *BootDrive = atoi(p) + 0x80;
        p = strchr(p, ')');
        if ((p == NULL) || (_strnicmp(p, ")partition(", 11) != 0))
            return FALSE;
        p = p + 11;
        *BootPartition = atoi(p);
        p = strchr(p, ')');
        if (p == NULL)
            return FALSE;
        p++;
    }
    else
    {
        return FALSE;
    }

    strcpy(BootPath, p);

    return TRUE;
}
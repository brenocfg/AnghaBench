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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
typedef  int UCHAR ;
typedef  char* PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

VOID ConstructArcPath(PCHAR ArcPath, PCHAR SystemFolder, UCHAR Disk, ULONG Partition)
{
    char    tmp[50];

    strcpy(ArcPath, "multi(0)disk(0)");

    if (Disk < 0x80)
    {
        /*
         * Floppy disk path:
         *  multi(0)disk(0)fdisk(x)\path
         */
        sprintf(tmp, "fdisk(%d)", (int) Disk);
        strcat(ArcPath, tmp);
    }
    else
    {
        /*
         * Hard disk path:
         *  multi(0)disk(0)rdisk(x)partition(y)\path
         */
        sprintf(tmp, "rdisk(%d)partition(%d)", (int) (Disk - 0x80), (int) Partition);
        strcat(ArcPath, tmp);
    }

    if (SystemFolder[0] == '\\' || SystemFolder[0] == '/')
    {
        strcat(ArcPath, SystemFolder);
    }
    else
    {
        strcat(ArcPath, "\\");
        strcat(ArcPath, SystemFolder);
    }
}
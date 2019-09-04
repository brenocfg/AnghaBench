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
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DiskIsDriveRemovable(UCHAR DriveNumber)
{
    /*
     * Hard disks use drive numbers >= 0x80 . So if the drive number
     * indicates a hard disk then return FALSE.
     * 0x49 is our magic ramdisk drive, so return FALSE for that too.
     */
    if ((DriveNumber >= 0x80) || (DriveNumber == 0x49))
        return FALSE;

    /* The drive is a floppy diskette so return TRUE */
    return TRUE;
}
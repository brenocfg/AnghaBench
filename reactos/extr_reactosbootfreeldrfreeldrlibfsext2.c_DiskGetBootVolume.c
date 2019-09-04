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
typedef  scalar_t__* PULONGLONG ;
typedef  scalar_t__* PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

BOOLEAN DiskGetBootVolume(PUCHAR DriveNumber, PULONGLONG StartSector, PULONGLONG SectorCount, int *FsType)
{
    *DriveNumber = 0;
    *StartSector = 0;
    *SectorCount = 0;
    *FsType = 0;
    return FALSE;
}
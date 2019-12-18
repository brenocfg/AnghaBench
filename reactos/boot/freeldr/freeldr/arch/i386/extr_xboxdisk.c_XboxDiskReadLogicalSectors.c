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
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int UCHAR ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDE_CMD_READ ; 
 int IDE_DH_DRV0 ; 
 int IDE_DH_DRV1 ; 
 int IDE_DH_LBA ; 
 int IDE_SECTOR_BUF_SZ ; 
 int /*<<< orphan*/  TRUE ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  XBOX_IDE_COMMAND_PORT ; 
 int /*<<< orphan*/  XBOX_IDE_CONTROL_PORT ; 
 int /*<<< orphan*/  XboxDiskPolledRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,scalar_t__) ; 

BOOLEAN
XboxDiskReadLogicalSectors(UCHAR DriveNumber, ULONGLONG SectorNumber, ULONG SectorCount, PVOID Buffer)
{
    ULONG StartSector;
    UCHAR Count;

    if (DriveNumber < 0x80 || (DriveNumber & 0x0f) >= 2)
    {
        /* Xbox has only 1 IDE controller and no floppy */
        WARN("Invalid drive number\n");
        return FALSE;
    }

    if (((SectorNumber + SectorCount) & UINT64_C(0xfffffffff0000000)) != UINT64_C(0))
    {
        FIXME("48bit LBA required but not implemented\n");
        return FALSE;
    }

    StartSector = (ULONG) SectorNumber;
    while (SectorCount > 0)
    {
        Count = (SectorCount <= 255 ? (UCHAR)SectorCount : 255);
        if (!XboxDiskPolledRead(XBOX_IDE_COMMAND_PORT,
                                XBOX_IDE_CONTROL_PORT,
                                0, Count,
                                StartSector & 0xff,
                                (StartSector >> 8) & 0xff,
                                (StartSector >> 16) & 0xff,
                                ((StartSector >> 24) & 0x0f) | IDE_DH_LBA |
                                ((DriveNumber & 0x0f) == 0 ? IDE_DH_DRV0 : IDE_DH_DRV1),
                                IDE_CMD_READ,
                                Buffer))
        {
            return FALSE;
        }
        SectorCount -= Count;
        Buffer = (PVOID) ((PCHAR) Buffer + Count * IDE_SECTOR_BUF_SZ);
    }

    return TRUE;
}
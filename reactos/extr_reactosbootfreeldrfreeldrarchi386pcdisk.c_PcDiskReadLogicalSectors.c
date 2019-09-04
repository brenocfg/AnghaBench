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
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ DiskInt13ExtensionsSupported (int) ; 
 scalar_t__ PcDiskReadLogicalSectorsCHS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PcDiskReadLogicalSectorsLBA (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,char*,...) ; 
 scalar_t__ TRUE ; 

BOOLEAN PcDiskReadLogicalSectors(UCHAR DriveNumber, ULONGLONG SectorNumber, ULONG SectorCount, PVOID Buffer)
{
    BOOLEAN ExtensionsSupported;

    TRACE("PcDiskReadLogicalSectors() DriveNumber: 0x%x SectorNumber: %I64d SectorCount: %d Buffer: 0x%x\n",
          DriveNumber, SectorNumber, SectorCount, Buffer);

    /*
     * Check to see if it is a fixed disk drive.
     * If so then check to see if Int13 extensions work.
     * If they do then use them, otherwise default back to BIOS calls.
     */
    ExtensionsSupported = DiskInt13ExtensionsSupported(DriveNumber);

    if ((DriveNumber >= 0x80) && ExtensionsSupported)
    {
        TRACE("Using Int 13 Extensions for read. DiskInt13ExtensionsSupported(%d) = %s\n", DriveNumber, ExtensionsSupported ? "TRUE" : "FALSE");

        /* LBA is easy, nothing to calculate. Just do the read. */
        return PcDiskReadLogicalSectorsLBA(DriveNumber, SectorNumber, SectorCount, Buffer);
    }
    else
    {
        /* LBA is not supported default to the CHS calls */
        return PcDiskReadLogicalSectorsCHS(DriveNumber, SectorNumber, SectorCount, Buffer);
    }

    return TRUE;
}
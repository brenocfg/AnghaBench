#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int UCHAR ;
struct TYPE_6__ {int MasterBootRecordMagic; TYPE_1__* PartitionTable; } ;
struct TYPE_5__ {int BootIndicator; int StartHead; int StartSector; int StartCylinder; int SystemIndicator; int EndHead; int EndSector; int EndCylinder; int SectorCountBeforePartition; int PartitionSectorCount; } ;
typedef  TYPE_2__* PMASTER_BOOT_RECORD ;
typedef  int /*<<< orphan*/  MASTER_BOOT_RECORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DiskReadBuffer ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MachDiskReadLogicalSectors (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DiskReadBootRecord(UCHAR DriveNumber, ULONGLONG LogicalSectorNumber, PMASTER_BOOT_RECORD BootRecord)
{
    ULONG Index;

    // Read master boot record
    if (!MachDiskReadLogicalSectors(DriveNumber, LogicalSectorNumber, 1, DiskReadBuffer))
    {
        return FALSE;
    }
    RtlCopyMemory(BootRecord, DiskReadBuffer, sizeof(MASTER_BOOT_RECORD));

    TRACE("Dumping partition table for drive 0x%x:\n", DriveNumber);
    TRACE("Boot record logical start sector = %d\n", LogicalSectorNumber);
    TRACE("sizeof(MASTER_BOOT_RECORD) = 0x%x.\n", sizeof(MASTER_BOOT_RECORD));

    for (Index=0; Index<4; Index++)
    {
        TRACE("-------------------------------------------\n");
        TRACE("Partition %d\n", (Index + 1));
        TRACE("BootIndicator: 0x%x\n", BootRecord->PartitionTable[Index].BootIndicator);
        TRACE("StartHead: 0x%x\n", BootRecord->PartitionTable[Index].StartHead);
        TRACE("StartSector (Plus 2 cylinder bits): 0x%x\n", BootRecord->PartitionTable[Index].StartSector);
        TRACE("StartCylinder: 0x%x\n", BootRecord->PartitionTable[Index].StartCylinder);
        TRACE("SystemIndicator: 0x%x\n", BootRecord->PartitionTable[Index].SystemIndicator);
        TRACE("EndHead: 0x%x\n", BootRecord->PartitionTable[Index].EndHead);
        TRACE("EndSector (Plus 2 cylinder bits): 0x%x\n", BootRecord->PartitionTable[Index].EndSector);
        TRACE("EndCylinder: 0x%x\n", BootRecord->PartitionTable[Index].EndCylinder);
        TRACE("SectorCountBeforePartition: 0x%x\n", BootRecord->PartitionTable[Index].SectorCountBeforePartition);
        TRACE("PartitionSectorCount: 0x%x\n", BootRecord->PartitionTable[Index].PartitionSectorCount);
    }

    // Check the partition table magic value
    if (BootRecord->MasterBootRecordMagic != 0xaa55)
    {
        return FALSE;
    }

    return TRUE;
}
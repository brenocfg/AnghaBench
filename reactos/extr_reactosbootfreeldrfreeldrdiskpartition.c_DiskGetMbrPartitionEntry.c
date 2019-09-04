#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_14__ {TYPE_1__* PartitionTable; } ;
struct TYPE_13__ {int SectorCountBeforePartition; } ;
struct TYPE_12__ {scalar_t__ SystemIndicator; int /*<<< orphan*/  SectorCountBeforePartition; } ;
typedef  TYPE_1__* PPARTITION_TABLE_ENTRY ;
typedef  TYPE_2__ PARTITION_TABLE_ENTRY ;
typedef  TYPE_3__ MASTER_BOOT_RECORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DiskGetFirstExtendedPartitionEntry (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DiskGetFirstPartitionEntry (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DiskReadBootRecord (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARTITION_ENTRY_UNUSED ; 
 scalar_t__ PARTITION_EXTENDED ; 
 scalar_t__ PARTITION_XINT13_EXTENDED ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DiskGetMbrPartitionEntry(UCHAR DriveNumber, ULONG PartitionNumber, PPARTITION_TABLE_ENTRY PartitionTableEntry)
{
    MASTER_BOOT_RECORD MasterBootRecord;
    PARTITION_TABLE_ENTRY ExtendedPartitionTableEntry;
    ULONG ExtendedPartitionNumber;
    ULONG ExtendedPartitionOffset;
    ULONG Index;
    ULONG CurrentPartitionNumber;
    PPARTITION_TABLE_ENTRY ThisPartitionTableEntry;

    // Read master boot record
    if (!DiskReadBootRecord(DriveNumber, 0, &MasterBootRecord))
    {
        return FALSE;
    }

    CurrentPartitionNumber = 0;
    for (Index=0; Index<4; Index++)
    {
        ThisPartitionTableEntry = &MasterBootRecord.PartitionTable[Index];

        if (ThisPartitionTableEntry->SystemIndicator != PARTITION_ENTRY_UNUSED &&
            ThisPartitionTableEntry->SystemIndicator != PARTITION_EXTENDED &&
            ThisPartitionTableEntry->SystemIndicator != PARTITION_XINT13_EXTENDED)
        {
            CurrentPartitionNumber++;
        }

        if (PartitionNumber == CurrentPartitionNumber)
        {
            RtlCopyMemory(PartitionTableEntry, ThisPartitionTableEntry, sizeof(PARTITION_TABLE_ENTRY));
            return TRUE;
        }
    }

    // They want an extended partition entry so we will need
    // to loop through all the extended partitions on the disk
    // and return the one they want.

    ExtendedPartitionNumber = PartitionNumber - CurrentPartitionNumber - 1;

    // Set the initial relative starting sector to 0
    // This is because extended partition starting
    // sectors a numbered relative to their parent
    ExtendedPartitionOffset = 0;

    for (Index=0; Index<=ExtendedPartitionNumber; Index++)
    {
        // Get the extended partition table entry
        if (!DiskGetFirstExtendedPartitionEntry(&MasterBootRecord, &ExtendedPartitionTableEntry))
        {
            return FALSE;
        }

        // Adjust the relative starting sector of the partition
        ExtendedPartitionTableEntry.SectorCountBeforePartition += ExtendedPartitionOffset;
        if (ExtendedPartitionOffset == 0)
        {
            // Set the start of the parrent extended partition
            ExtendedPartitionOffset = ExtendedPartitionTableEntry.SectorCountBeforePartition;
        }
        // Read the partition boot record
        if (!DiskReadBootRecord(DriveNumber, ExtendedPartitionTableEntry.SectorCountBeforePartition, &MasterBootRecord))
        {
            return FALSE;
        }

        // Get the first real partition table entry
        if (!DiskGetFirstPartitionEntry(&MasterBootRecord, PartitionTableEntry))
        {
            return FALSE;
        }

        // Now correct the start sector of the partition
        PartitionTableEntry->SectorCountBeforePartition += ExtendedPartitionTableEntry.SectorCountBeforePartition;
    }

    // When we get here we should have the correct entry
    // already stored in PartitionTableEntry
    // so just return TRUE
    return TRUE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {TYPE_1__* PartitionTable; } ;
struct TYPE_7__ {scalar_t__ SystemIndicator; int BootIndicator; } ;
typedef  TYPE_1__* PPARTITION_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  PARTITION_TABLE_ENTRY ;
typedef  TYPE_2__ MASTER_BOOT_RECORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DiskReadBootRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARTITION_ENTRY_UNUSED ; 
 scalar_t__ PARTITION_EXTENDED ; 
 scalar_t__ PARTITION_XINT13_EXTENDED ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DiskGetActivePartitionEntry(UCHAR DriveNumber,
                                    PPARTITION_TABLE_ENTRY PartitionTableEntry,
                                    ULONG *ActivePartition)
{
    ULONG BootablePartitionCount = 0;
    ULONG CurrentPartitionNumber;
    ULONG Index;
    MASTER_BOOT_RECORD MasterBootRecord;
    PPARTITION_TABLE_ENTRY ThisPartitionTableEntry;

    *ActivePartition = 0;

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

            // Test if this is the bootable partition
            if (ThisPartitionTableEntry->BootIndicator == 0x80)
            {
                BootablePartitionCount++;
                *ActivePartition = CurrentPartitionNumber;

                // Copy the partition table entry
                RtlCopyMemory(PartitionTableEntry,
                              ThisPartitionTableEntry,
                              sizeof(PARTITION_TABLE_ENTRY));
            }
        }
    }

    // Make sure there was only one bootable partition
    if (BootablePartitionCount == 0)
    {
        ERR("No bootable (active) partitions found.\n");
        return FALSE;
    }
    else if (BootablePartitionCount != 1)
    {
        ERR("Too many bootable (active) partitions found.\n");
        return FALSE;
    }

    return TRUE;
}
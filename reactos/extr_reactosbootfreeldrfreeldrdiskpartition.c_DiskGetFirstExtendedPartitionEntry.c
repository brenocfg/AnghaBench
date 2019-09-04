#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_5__ {scalar_t__ SystemIndicator; } ;
struct TYPE_4__ {TYPE_2__* PartitionTable; } ;
typedef  int /*<<< orphan*/  PPARTITION_TABLE_ENTRY ;
typedef  TYPE_1__* PMASTER_BOOT_RECORD ;
typedef  int /*<<< orphan*/  PARTITION_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARTITION_EXTENDED ; 
 scalar_t__ PARTITION_XINT13_EXTENDED ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DiskGetFirstExtendedPartitionEntry(PMASTER_BOOT_RECORD MasterBootRecord, PPARTITION_TABLE_ENTRY PartitionTableEntry)
{
    ULONG Index;

    for (Index=0; Index<4; Index++)
    {
        // Check the system indicator
        // If it an extended partition then we're done
        if ((MasterBootRecord->PartitionTable[Index].SystemIndicator == PARTITION_EXTENDED) ||
            (MasterBootRecord->PartitionTable[Index].SystemIndicator == PARTITION_XINT13_EXTENDED))
        {
            RtlCopyMemory(PartitionTableEntry, &MasterBootRecord->PartitionTable[Index], sizeof(PARTITION_TABLE_ENTRY));
            return TRUE;
        }
    }

    return FALSE;
}
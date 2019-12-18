#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_26__ {scalar_t__ LowPart; scalar_t__ QuadPart; } ;
struct TYPE_18__ {scalar_t__ BytesPerCluster; } ;
struct TYPE_25__ {TYPE_1__ NtfsInfo; } ;
struct TYPE_24__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_23__ {TYPE_3__* pRecord; int /*<<< orphan*/  DataRunsMCB; } ;
struct TYPE_21__ {scalar_t__ AllocatedSize; scalar_t__ HighestVCN; int /*<<< orphan*/  InitializedSize; int /*<<< orphan*/  DataSize; } ;
struct TYPE_22__ {TYPE_4__ NonResident; } ;
struct TYPE_19__ {scalar_t__ AllocatedSize; scalar_t__ HighestVCN; int /*<<< orphan*/  InitializedSize; int /*<<< orphan*/  DataSize; } ;
struct TYPE_20__ {TYPE_2__ NonResident; int /*<<< orphan*/  IsNonResident; } ;
typedef  TYPE_5__* PNTFS_ATTR_RECORD ;
typedef  TYPE_6__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/  PLONGLONG ;
typedef  TYPE_7__* PLARGE_INTEGER ;
typedef  scalar_t__ PFILE_RECORD_HEADER ;
typedef  TYPE_8__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LONGLONG ;
typedef  TYPE_9__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddRun (TYPE_8__*,TYPE_6__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  FreeClusters (TYPE_8__*,TYPE_6__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FsRtlLookupLargeMcbEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsAllocateClusters (TYPE_8__*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ ROUND_UP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
SetNonResidentAttributeDataLength(PDEVICE_EXTENSION Vcb,
                                  PNTFS_ATTR_CONTEXT AttrContext,
                                  ULONG AttrOffset,
                                  PFILE_RECORD_HEADER FileRecord,
                                  PLARGE_INTEGER DataSize)
{
    NTSTATUS Status = STATUS_SUCCESS;
    ULONG BytesPerCluster = Vcb->NtfsInfo.BytesPerCluster;
    ULONGLONG AllocationSize = ROUND_UP(DataSize->QuadPart, BytesPerCluster);
    PNTFS_ATTR_RECORD DestinationAttribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)FileRecord + AttrOffset);
    ULONG ExistingClusters = AttrContext->pRecord->NonResident.AllocatedSize / BytesPerCluster;

    ASSERT(AttrContext->pRecord->IsNonResident);

    // do we need to increase the allocation size?
    if (AttrContext->pRecord->NonResident.AllocatedSize < AllocationSize)
    {
        ULONG ClustersNeeded = (AllocationSize / BytesPerCluster) - ExistingClusters;
        LARGE_INTEGER LastClusterInDataRun;
        ULONG NextAssignedCluster;
        ULONG AssignedClusters;

        if (ExistingClusters == 0)
        {
            LastClusterInDataRun.QuadPart = 0;
        }
        else
        {
            if (!FsRtlLookupLargeMcbEntry(&AttrContext->DataRunsMCB,
                                          (LONGLONG)AttrContext->pRecord->NonResident.HighestVCN,
                                          (PLONGLONG)&LastClusterInDataRun.QuadPart,
                                          NULL,
                                          NULL,
                                          NULL,
                                          NULL))
            {
                DPRINT1("Error looking up final large MCB entry!\n");

                // Most likely, HighestVCN went above the largest mapping
                DPRINT1("Highest VCN of record: %I64u\n", AttrContext->pRecord->NonResident.HighestVCN);
                return STATUS_INVALID_PARAMETER;
            }
        }

        DPRINT("LastClusterInDataRun: %I64u\n", LastClusterInDataRun.QuadPart);
        DPRINT("Highest VCN of record: %I64u\n", AttrContext->pRecord->NonResident.HighestVCN);

        while (ClustersNeeded > 0)
        {
            Status = NtfsAllocateClusters(Vcb,
                                          LastClusterInDataRun.LowPart + 1,
                                          ClustersNeeded,
                                          &NextAssignedCluster,
                                          &AssignedClusters);

            if (!NT_SUCCESS(Status))
            {
                DPRINT1("Error: Unable to allocate requested clusters!\n");
                return Status;
            }

            // now we need to add the clusters we allocated to the data run
            Status = AddRun(Vcb, AttrContext, AttrOffset, FileRecord, NextAssignedCluster, AssignedClusters);
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("Error: Unable to add data run!\n");
                return Status;
            }

            ClustersNeeded -= AssignedClusters;
            LastClusterInDataRun.LowPart = NextAssignedCluster + AssignedClusters - 1;
        }
    }
    else if (AttrContext->pRecord->NonResident.AllocatedSize > AllocationSize)
    {
        // shrink allocation size
        ULONG ClustersToFree = ExistingClusters - (AllocationSize / BytesPerCluster);
        Status = FreeClusters(Vcb, AttrContext, AttrOffset, FileRecord, ClustersToFree);
    }

    // TODO: is the file compressed, encrypted, or sparse?

    AttrContext->pRecord->NonResident.AllocatedSize = AllocationSize;
    AttrContext->pRecord->NonResident.DataSize = DataSize->QuadPart;
    AttrContext->pRecord->NonResident.InitializedSize = DataSize->QuadPart;

    DestinationAttribute->NonResident.AllocatedSize = AllocationSize;
    DestinationAttribute->NonResident.DataSize = DataSize->QuadPart;
    DestinationAttribute->NonResident.InitializedSize = DataSize->QuadPart;
    
    // HighestVCN seems to be set incorrectly somewhere. Apply a hack-fix to reset it. 
    // HACKHACK FIXME: Fix for sparse files; this math won't work in that case.
    AttrContext->pRecord->NonResident.HighestVCN = ((ULONGLONG)AllocationSize / Vcb->NtfsInfo.BytesPerCluster) - 1;
    DestinationAttribute->NonResident.HighestVCN = AttrContext->pRecord->NonResident.HighestVCN;

    DPRINT("Allocated Size: %I64u\n", DestinationAttribute->NonResident.AllocatedSize);

    return Status;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_13__ {int ClusterCount; int BytesPerSector; int SectorsPerCluster; } ;
struct TYPE_15__ {int /*<<< orphan*/  FileRecLookasideList; TYPE_1__ NtfsInfo; } ;
struct TYPE_14__ {int /*<<< orphan*/  pRecord; } ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_2__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/ * PFILE_RECORD_HEADER ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AttributeData ; 
 int AttributeDataLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindAttribute (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NTFS_FILE_BITMAP ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ROUND_UP (int,int) ; 
 int /*<<< orphan*/  ReadAttribute (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReadFileRecord (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_2__*) ; 
 int RtlFindClearBitsAndSet (int /*<<< orphan*/ *,int,int) ; 
 int RtlFindLongestRunClear (int /*<<< orphan*/ *,int*) ; 
 int RtlFindNextForwardRunClear (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int*,int) ; 
 int RtlNumberOfClearBits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_DISK_FULL ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int /*<<< orphan*/  WriteAttribute (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int min (int,int) ; 

NTSTATUS
NtfsAllocateClusters(PDEVICE_EXTENSION DeviceExt,
                     ULONG FirstDesiredCluster,
                     ULONG DesiredClusters, 
                     PULONG FirstAssignedCluster, 
                     PULONG AssignedClusters)
{
    NTSTATUS Status;
    PFILE_RECORD_HEADER BitmapRecord;
    PNTFS_ATTR_CONTEXT DataContext;
    ULONGLONG BitmapDataSize;
    PUCHAR BitmapData;
    ULONGLONG FreeClusters = 0;
    RTL_BITMAP Bitmap;
    ULONG AssignedRun;
    ULONG LengthWritten;

    DPRINT("NtfsAllocateClusters(%p, %lu, %lu, %p, %p)\n", DeviceExt, FirstDesiredCluster, DesiredClusters, FirstAssignedCluster, AssignedClusters);

    BitmapRecord = ExAllocateFromNPagedLookasideList(&DeviceExt->FileRecLookasideList);
    if (BitmapRecord == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = ReadFileRecord(DeviceExt, NTFS_FILE_BITMAP, BitmapRecord);
    if (!NT_SUCCESS(Status))
    {
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);
        return Status;
    }

    Status = FindAttribute(DeviceExt, BitmapRecord, AttributeData, L"", 0, &DataContext, NULL);
    if (!NT_SUCCESS(Status))
    {
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);
        return Status;
    }

    BitmapDataSize = AttributeDataLength(DataContext->pRecord);
    BitmapDataSize = min(BitmapDataSize, 0xffffffff);
    ASSERT((BitmapDataSize * 8) >= DeviceExt->NtfsInfo.ClusterCount);
    BitmapData = ExAllocatePoolWithTag(NonPagedPool, ROUND_UP(BitmapDataSize, DeviceExt->NtfsInfo.BytesPerSector), TAG_NTFS);
    if (BitmapData == NULL)
    {
        ReleaseAttributeContext(DataContext);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);
        return  STATUS_INSUFFICIENT_RESOURCES;
    }

    DPRINT("Total clusters: %I64x\n", DeviceExt->NtfsInfo.ClusterCount);
    DPRINT("Total clusters in bitmap: %I64x\n", BitmapDataSize * 8);
    DPRINT("Diff in size: %I64d B\n", ((BitmapDataSize * 8) - DeviceExt->NtfsInfo.ClusterCount) * DeviceExt->NtfsInfo.SectorsPerCluster * DeviceExt->NtfsInfo.BytesPerSector);

    ReadAttribute(DeviceExt, DataContext, 0, (PCHAR)BitmapData, (ULONG)BitmapDataSize);

    RtlInitializeBitMap(&Bitmap, (PULONG)BitmapData, DeviceExt->NtfsInfo.ClusterCount);
    FreeClusters = RtlNumberOfClearBits(&Bitmap);

    if (FreeClusters < DesiredClusters)
    {
        ReleaseAttributeContext(DataContext);

        ExFreePoolWithTag(BitmapData, TAG_NTFS);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);
        return STATUS_DISK_FULL;
    }
    
    // TODO: Observe MFT reservation zone

    // Can we get one contiguous run?
    AssignedRun = RtlFindClearBitsAndSet(&Bitmap, DesiredClusters, FirstDesiredCluster);

    if (AssignedRun != 0xFFFFFFFF)
    {
        *FirstAssignedCluster = AssignedRun;
        *AssignedClusters = DesiredClusters;
    }
    else
    {
        // we can't get one contiguous run
        *AssignedClusters = RtlFindNextForwardRunClear(&Bitmap, FirstDesiredCluster, FirstAssignedCluster);
        
        if (*AssignedClusters == 0)
        {
            // we couldn't find any runs starting at DesiredFirstCluster
            *AssignedClusters = RtlFindLongestRunClear(&Bitmap, FirstAssignedCluster);
        }
            
    }
                
    Status = WriteAttribute(DeviceExt, DataContext, 0, BitmapData, (ULONG)BitmapDataSize, &LengthWritten, BitmapRecord);
    
    ReleaseAttributeContext(DataContext);

    ExFreePoolWithTag(BitmapData, TAG_NTFS);
    ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);

    return Status;
}
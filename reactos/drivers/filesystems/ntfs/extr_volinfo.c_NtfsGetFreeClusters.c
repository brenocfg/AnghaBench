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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_12__ {int ClusterCount; int BytesPerSector; int SectorsPerCluster; } ;
struct TYPE_14__ {int /*<<< orphan*/  FileRecLookasideList; TYPE_1__ NtfsInfo; } ;
struct TYPE_13__ {int /*<<< orphan*/  pRecord; } ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_2__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/ * PFILE_RECORD_HEADER ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AttributeData ; 
 int AttributeDataLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindAttribute (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NTFS_FILE_BITMAP ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ROUND_UP (int,int) ; 
 int /*<<< orphan*/  ReadAttribute (TYPE_3__*,TYPE_2__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReadFileRecord (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_2__*) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int RtlNumberOfClearBits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG_NTFS ; 

ULONGLONG
NtfsGetFreeClusters(PDEVICE_EXTENSION DeviceExt)
{
    NTSTATUS Status;
    PFILE_RECORD_HEADER BitmapRecord;
    PNTFS_ATTR_CONTEXT DataContext;
    ULONGLONG BitmapDataSize;
    PCHAR BitmapData;
    ULONGLONG FreeClusters = 0;
    ULONG Read = 0;
    RTL_BITMAP Bitmap;

    DPRINT("NtfsGetFreeClusters(%p)\n", DeviceExt);

    BitmapRecord = ExAllocateFromNPagedLookasideList(&DeviceExt->FileRecLookasideList);
    if (BitmapRecord == NULL)
    {
        return 0;
    }

    Status = ReadFileRecord(DeviceExt, NTFS_FILE_BITMAP, BitmapRecord);
    if (!NT_SUCCESS(Status))
    {
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);
        return 0;
    }

    Status = FindAttribute(DeviceExt, BitmapRecord, AttributeData, L"", 0, &DataContext, NULL);
    if (!NT_SUCCESS(Status))
    {
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);
        return 0;
    }

    BitmapDataSize = AttributeDataLength(DataContext->pRecord);
    ASSERT((BitmapDataSize * 8) >= DeviceExt->NtfsInfo.ClusterCount);
    BitmapData = ExAllocatePoolWithTag(NonPagedPool, ROUND_UP(BitmapDataSize, DeviceExt->NtfsInfo.BytesPerSector), TAG_NTFS);
    if (BitmapData == NULL)
    {
        ReleaseAttributeContext(DataContext);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);
        return 0;
    }

    /* FIXME: Totally underoptimized! */
    for (; Read < BitmapDataSize; Read += DeviceExt->NtfsInfo.BytesPerSector)
    {
        ReadAttribute(DeviceExt, DataContext, Read, (PCHAR)((ULONG_PTR)BitmapData + Read), DeviceExt->NtfsInfo.BytesPerSector);
    }
    ReleaseAttributeContext(DataContext);

    DPRINT1("Total clusters: %I64x\n", DeviceExt->NtfsInfo.ClusterCount);
    DPRINT1("Total clusters in bitmap: %I64x\n", BitmapDataSize * 8);
    DPRINT1("Diff in size: %I64d B\n", ((BitmapDataSize * 8) - DeviceExt->NtfsInfo.ClusterCount) * DeviceExt->NtfsInfo.SectorsPerCluster * DeviceExt->NtfsInfo.BytesPerSector);

    RtlInitializeBitMap(&Bitmap, (PULONG)BitmapData, DeviceExt->NtfsInfo.ClusterCount);
    FreeClusters = RtlNumberOfClearBits(&Bitmap);

    ExFreePoolWithTag(BitmapData, TAG_NTFS);
    ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, BitmapRecord);

    return FreeClusters;
}
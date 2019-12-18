#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_56__   TYPE_9__ ;
typedef  struct TYPE_55__   TYPE_8__ ;
typedef  struct TYPE_54__   TYPE_7__ ;
typedef  struct TYPE_53__   TYPE_6__ ;
typedef  struct TYPE_52__   TYPE_5__ ;
typedef  struct TYPE_51__   TYPE_4__ ;
typedef  struct TYPE_50__   TYPE_3__ ;
typedef  struct TYPE_49__   TYPE_2__ ;
typedef  struct TYPE_48__   TYPE_24__ ;
typedef  struct TYPE_47__   TYPE_23__ ;
typedef  struct TYPE_46__   TYPE_22__ ;
typedef  struct TYPE_45__   TYPE_21__ ;
typedef  struct TYPE_44__   TYPE_20__ ;
typedef  struct TYPE_43__   TYPE_1__ ;
typedef  struct TYPE_42__   TYPE_19__ ;
typedef  struct TYPE_41__   TYPE_18__ ;
typedef  struct TYPE_40__   TYPE_17__ ;
typedef  struct TYPE_39__   TYPE_16__ ;
typedef  struct TYPE_38__   TYPE_15__ ;
typedef  struct TYPE_37__   TYPE_14__ ;
typedef  struct TYPE_36__   TYPE_13__ ;
typedef  struct TYPE_35__   TYPE_12__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_56__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_55__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_54__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_53__ {long long QuadPart; } ;
struct TYPE_52__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_51__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_50__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_49__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_33__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_40__ {int BytesPerCluster; int BytesPerFileRecord; int /*<<< orphan*/  MinorVersion; int /*<<< orphan*/  MajorVersion; TYPE_10__ MftMirrStart; TYPE_8__ MftStart; int /*<<< orphan*/  BytesPerSector; int /*<<< orphan*/  ClusterCount; int /*<<< orphan*/  SectorCount; int /*<<< orphan*/  SerialNumber; } ;
struct TYPE_48__ {TYPE_17__ NtfsInfo; int /*<<< orphan*/  MasterFileTable; } ;
struct TYPE_38__ {int OutputBufferLength; } ;
struct TYPE_39__ {TYPE_15__ FileSystemControl; } ;
struct TYPE_47__ {TYPE_16__ Parameters; } ;
struct TYPE_41__ {int Information; } ;
struct TYPE_43__ {scalar_t__ SystemBuffer; } ;
struct TYPE_46__ {TYPE_18__ IoStatus; int /*<<< orphan*/ * UserBuffer; TYPE_1__ AssociatedIrp; } ;
struct TYPE_37__ {int /*<<< orphan*/  DataSize; } ;
struct TYPE_45__ {scalar_t__ Type; TYPE_14__ NonResident; int /*<<< orphan*/  IsNonResident; } ;
struct TYPE_44__ {int ByteCount; int /*<<< orphan*/  MinorVersion; int /*<<< orphan*/  MajorVersion; } ;
struct TYPE_36__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_35__ {scalar_t__ QuadPart; } ;
struct TYPE_34__ {scalar_t__ QuadPart; } ;
struct TYPE_42__ {int BytesPerCluster; int BytesPerFileRecordSegment; int ClustersPerFileRecordSegment; TYPE_13__ MftValidDataLength; TYPE_12__ MftZoneEnd; TYPE_11__ MftZoneStart; TYPE_9__ Mft2StartLcn; TYPE_7__ MftStartLcn; int /*<<< orphan*/  BytesPerSector; TYPE_6__ TotalReserved; TYPE_5__ FreeClusters; TYPE_4__ TotalClusters; TYPE_3__ NumberSectors; TYPE_2__ VolumeSerialNumber; } ;
typedef  TYPE_19__* PNTFS_VOLUME_DATA_BUFFER ;
typedef  TYPE_20__* PNTFS_EXTENDED_VOLUME_DATA ;
typedef  TYPE_21__* PNTFS_ATTR_RECORD ;
typedef  TYPE_22__* PIRP ;
typedef  TYPE_23__* PIO_STACK_LOCATION ;
typedef  TYPE_24__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NTFS_VOLUME_DATA_BUFFER ;
typedef  int /*<<< orphan*/  NTFS_EXTENDED_VOLUME_DATA ;
typedef  int /*<<< orphan*/  FIND_ATTR_CONTXT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ AttributeData ; 
 int /*<<< orphan*/  DPRINT1 (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindCloseAttribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindFirstAttribute (int /*<<< orphan*/ *,TYPE_24__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_21__**) ; 
 int /*<<< orphan*/  FindNextAttribute (int /*<<< orphan*/ *,TYPE_21__**) ; 
 TYPE_23__* IoGetCurrentIrpStackLocation (TYPE_22__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsGetFreeClusters (TYPE_24__*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
GetNfsVolumeData(PDEVICE_EXTENSION DeviceExt,
                 PIRP Irp)
{
    PIO_STACK_LOCATION Stack;
    PNTFS_VOLUME_DATA_BUFFER DataBuffer;
    PNTFS_ATTR_RECORD Attribute;
    FIND_ATTR_CONTXT Context;
    NTSTATUS Status;

    DataBuffer = (PNTFS_VOLUME_DATA_BUFFER)Irp->AssociatedIrp.SystemBuffer;
    Stack = IoGetCurrentIrpStackLocation(Irp);

    if (Stack->Parameters.FileSystemControl.OutputBufferLength < sizeof(NTFS_VOLUME_DATA_BUFFER) ||
        Irp->UserBuffer == NULL)
    {
        DPRINT1("Invalid output! %d %p\n", Stack->Parameters.FileSystemControl.OutputBufferLength, Irp->UserBuffer);
        return STATUS_INVALID_PARAMETER;
    }

    DataBuffer->VolumeSerialNumber.QuadPart = DeviceExt->NtfsInfo.SerialNumber;
    DataBuffer->NumberSectors.QuadPart = DeviceExt->NtfsInfo.SectorCount;
    DataBuffer->TotalClusters.QuadPart = DeviceExt->NtfsInfo.ClusterCount;
    DataBuffer->FreeClusters.QuadPart = NtfsGetFreeClusters(DeviceExt);
    DataBuffer->TotalReserved.QuadPart = 0LL; // FIXME
    DataBuffer->BytesPerSector = DeviceExt->NtfsInfo.BytesPerSector;
    DataBuffer->BytesPerCluster = DeviceExt->NtfsInfo.BytesPerCluster;
    DataBuffer->BytesPerFileRecordSegment = DeviceExt->NtfsInfo.BytesPerFileRecord;
    DataBuffer->ClustersPerFileRecordSegment = DeviceExt->NtfsInfo.BytesPerFileRecord / DeviceExt->NtfsInfo.BytesPerCluster;
    DataBuffer->MftStartLcn.QuadPart = DeviceExt->NtfsInfo.MftStart.QuadPart;
    DataBuffer->Mft2StartLcn.QuadPart = DeviceExt->NtfsInfo.MftMirrStart.QuadPart;
    DataBuffer->MftZoneStart.QuadPart = 0; // FIXME
    DataBuffer->MftZoneEnd.QuadPart = 0; // FIXME

    Status = FindFirstAttribute(&Context, DeviceExt, DeviceExt->MasterFileTable, FALSE, &Attribute);
    while (NT_SUCCESS(Status))
    {
        if (Attribute->Type == AttributeData)
        {
            ASSERT(Attribute->IsNonResident);
            DataBuffer->MftValidDataLength.QuadPart = Attribute->NonResident.DataSize;

            break;
        }

        Status = FindNextAttribute(&Context, &Attribute);
    }
    FindCloseAttribute(&Context);

    Irp->IoStatus.Information = sizeof(NTFS_VOLUME_DATA_BUFFER);

    if (Stack->Parameters.FileSystemControl.OutputBufferLength >= sizeof(NTFS_EXTENDED_VOLUME_DATA) + sizeof(NTFS_VOLUME_DATA_BUFFER))
    {
        PNTFS_EXTENDED_VOLUME_DATA ExtendedData = (PNTFS_EXTENDED_VOLUME_DATA)((ULONG_PTR)Irp->UserBuffer + sizeof(NTFS_VOLUME_DATA_BUFFER));

        ExtendedData->ByteCount = sizeof(NTFS_EXTENDED_VOLUME_DATA);
        ExtendedData->MajorVersion = DeviceExt->NtfsInfo.MajorVersion;
        ExtendedData->MinorVersion = DeviceExt->NtfsInfo.MinorVersion;
        Irp->IoStatus.Information += sizeof(NTFS_EXTENDED_VOLUME_DATA);
    }

    return STATUS_SUCCESS;
}
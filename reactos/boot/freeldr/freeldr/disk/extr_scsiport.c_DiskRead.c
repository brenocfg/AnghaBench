#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
struct TYPE_11__ {int SectorSize; int SectorNumber; int SectorCount; int /*<<< orphan*/  DeviceExtension; int /*<<< orphan*/  Lun; int /*<<< orphan*/  TargetId; int /*<<< orphan*/  PathId; scalar_t__ SectorOffset; } ;
struct TYPE_8__ {int LogicalBlockByte0; int LogicalBlockByte1; int LogicalBlockByte2; int LogicalBlockByte3; int TransferBlocksMsb; int TransferBlocksLsb; int /*<<< orphan*/  LogicalUnitNumber; void* OperationCode; } ;
struct TYPE_10__ {TYPE_1__ CDB10; } ;
struct TYPE_9__ {int Length; int CdbLength; int DataTransferLength; int TimeOutValue; int /*<<< orphan*/  Lun; scalar_t__ Cdb; int /*<<< orphan*/ * DataBuffer; void* SrbFlags; int /*<<< orphan*/  TargetId; int /*<<< orphan*/  PathId; void* Function; } ;
typedef  int /*<<< orphan*/  SCSI_REQUEST_BLOCK ;
typedef  void* PUCHAR ;
typedef  TYPE_2__* PSCSI_REQUEST_BLOCK ;
typedef  TYPE_3__* PCDB ;
typedef  TYPE_4__ DISKCONTEXT ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ESUCCESS ; 
 void* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExFreePool (void*) ; 
 TYPE_4__* FsGetDeviceSpecific (int) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 void* SCSIOP_READ ; 
 void* SRB_FLAGS_DATA_IN ; 
 void* SRB_FUNCTION_EXECUTE_SCSI ; 
 int /*<<< orphan*/  SpiSendSynchronousSrb (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static ARC_STATUS DiskRead(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    DISKCONTEXT* Context = FsGetDeviceSpecific(FileId);
    PSCSI_REQUEST_BLOCK Srb;
    PCDB Cdb;
    ULONG FullSectors, NbSectors;
    ULONG Lba;

    *Count = 0;

    if (N == 0)
        return ESUCCESS;

    FullSectors = N / Context->SectorSize;
    NbSectors = (N + Context->SectorSize - 1) / Context->SectorSize;
    if (Context->SectorNumber + NbSectors >= Context->SectorCount)
        return EINVAL;
    if (FullSectors > 0xffff)
        return EINVAL;

    /* Read full sectors */
    ASSERT(Context->SectorNumber < 0xFFFFFFFF);
    Lba = (ULONG)(Context->SectorOffset + Context->SectorNumber);
    if (FullSectors > 0)
    {
        Srb = ExAllocatePool(PagedPool, sizeof(SCSI_REQUEST_BLOCK));
        if (!Srb)
            return ENOMEM;

        RtlZeroMemory(Srb, sizeof(SCSI_REQUEST_BLOCK));
        Srb->Length = sizeof(SCSI_REQUEST_BLOCK);
        Srb->Function = SRB_FUNCTION_EXECUTE_SCSI;
        Srb->PathId = Context->PathId;
        Srb->TargetId = Context->TargetId;
        Srb->Lun = Context->Lun;
        Srb->CdbLength = 10;
        Srb->SrbFlags = SRB_FLAGS_DATA_IN;
        Srb->DataTransferLength = FullSectors * Context->SectorSize;
        Srb->TimeOutValue = 5; /* in seconds */
        Srb->DataBuffer = Buffer;
        Cdb = (PCDB)Srb->Cdb;
        Cdb->CDB10.OperationCode = SCSIOP_READ;
        Cdb->CDB10.LogicalUnitNumber = Srb->Lun;
        Cdb->CDB10.LogicalBlockByte0 = (Lba >> 24) & 0xff;
        Cdb->CDB10.LogicalBlockByte1 = (Lba >> 16) & 0xff;
        Cdb->CDB10.LogicalBlockByte2 = (Lba >> 8) & 0xff;
        Cdb->CDB10.LogicalBlockByte3 = Lba & 0xff;
        Cdb->CDB10.TransferBlocksMsb = (FullSectors >> 8) & 0xff;
        Cdb->CDB10.TransferBlocksLsb = FullSectors & 0xff;
        if (!SpiSendSynchronousSrb(Context->DeviceExtension, Srb))
        {
            return EIO;
        }
        Buffer = (PUCHAR)Buffer + FullSectors * Context->SectorSize;
        N -= FullSectors * Context->SectorSize;
        *Count += FullSectors * Context->SectorSize;
        Context->SectorNumber += FullSectors;
        Lba += FullSectors;
    }

    /* Read incomplete last sector */
    if (N > 0)
    {
        PUCHAR Sector;

        Sector = ExAllocatePool(PagedPool, Context->SectorSize);
        if (!Sector)
            return ENOMEM;

        Srb = ExAllocatePool(PagedPool, sizeof(SCSI_REQUEST_BLOCK));
        if (!Srb)
        {
            ExFreePool(Sector);
            return ENOMEM;
        }

        RtlZeroMemory(Srb, sizeof(SCSI_REQUEST_BLOCK));
        Srb->Length = sizeof(SCSI_REQUEST_BLOCK);
        Srb->Function = SRB_FUNCTION_EXECUTE_SCSI;
        Srb->PathId = Context->PathId;
        Srb->TargetId = Context->TargetId;
        Srb->Lun = Context->Lun;
        Srb->CdbLength = 10;
        Srb->SrbFlags = SRB_FLAGS_DATA_IN;
        Srb->DataTransferLength = Context->SectorSize;
        Srb->TimeOutValue = 5; /* in seconds */
        Srb->DataBuffer = Sector;
        Cdb = (PCDB)Srb->Cdb;
        Cdb->CDB10.OperationCode = SCSIOP_READ;
        Cdb->CDB10.LogicalUnitNumber = Srb->Lun;
        Cdb->CDB10.LogicalBlockByte0 = (Lba >> 24) & 0xff;
        Cdb->CDB10.LogicalBlockByte1 = (Lba >> 16) & 0xff;
        Cdb->CDB10.LogicalBlockByte2 = (Lba >> 8) & 0xff;
        Cdb->CDB10.LogicalBlockByte3 = Lba & 0xff;
        Cdb->CDB10.TransferBlocksMsb = 0;
        Cdb->CDB10.TransferBlocksLsb = 1;
        if (!SpiSendSynchronousSrb(Context->DeviceExtension, Srb))
        {
            ExFreePool(Sector);
            return EIO;
        }
        RtlCopyMemory(Buffer, Sector, N);
        *Count += N;
        /* Context->SectorNumber remains untouched (incomplete sector read) */
        ExFreePool(Sector);
    }

    return ESUCCESS;
}
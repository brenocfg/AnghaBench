#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_28__ {TYPE_5__* Irp; } ;
struct TYPE_27__ {scalar_t__ OpenVolumeCount; scalar_t__ ReferenceCount; scalar_t__ OpenHandleCount; int /*<<< orphan*/  Vpb; TYPE_10__* LockFile; int /*<<< orphan*/  Flags; int /*<<< orphan*/  ShareAccess; } ;
struct TYPE_22__ {int Options; int ShareAccess; TYPE_1__* SecurityContext; } ;
struct TYPE_23__ {TYPE_2__ Create; } ;
struct TYPE_26__ {int Flags; TYPE_10__* FileObject; TYPE_3__ Parameters; } ;
struct TYPE_24__ {int /*<<< orphan*/  Information; } ;
struct TYPE_25__ {TYPE_4__ IoStatus; } ;
struct TYPE_21__ {int DesiredAccess; } ;
struct TYPE_20__ {int Flags; int /*<<< orphan*/  Vpb; int /*<<< orphan*/ * FsContext2; TYPE_7__* FsContext; } ;
typedef  TYPE_5__* PIRP ;
typedef  TYPE_6__* PIO_STACK_LOCATION ;
typedef  TYPE_7__* PEXT2_VCB ;
typedef  TYPE_8__* PEXT2_IRP_CONTEXT ;
typedef  int /*<<< orphan*/ * PEXT2_CCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;
typedef  int ACCESS_MASK ;

/* Variables and functions */
 int /*<<< orphan*/  DbgBreak () ; 
 int /*<<< orphan*/ * Ext2AllocateCcb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ext2FlushFiles (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2FlushVolume (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2ReferXcb (scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_DIRECTORY_FILE ; 
 int FILE_OPEN ; 
 int /*<<< orphan*/  FILE_OPENED ; 
 int FILE_OPEN_IF ; 
 int FILE_READ_DATA ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int FILE_WRITE_DATA ; 
 int FO_NO_INTERMEDIATE_BUFFERING ; 
 scalar_t__ FlagOn (int,int) ; 
 int /*<<< orphan*/  IoCheckShareAccess (int,int,TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* IoGetCurrentIrpStackLocation (TYPE_5__*) ; 
 int /*<<< orphan*/  IoSetShareAccess (int,int,TYPE_10__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IsFlagOn (int,int) ; 
 int /*<<< orphan*/  IsVcbReadOnly (TYPE_7__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int SL_OPEN_TARGET_DIRECTORY ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NOT_A_DIRECTORY ; 
 int /*<<< orphan*/  STATUS_SHARING_VIOLATION ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetLongFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VCB_VOLUME_LOCKED ; 

NTSTATUS
Ext2CreateVolume(PEXT2_IRP_CONTEXT IrpContext, PEXT2_VCB Vcb)
{
    PIO_STACK_LOCATION  IrpSp;
    PIRP                Irp;
    PEXT2_CCB           Ccb;

    NTSTATUS            Status;

    ACCESS_MASK         DesiredAccess;
    ULONG               ShareAccess;

    ULONG               Options;
    BOOLEAN             DirectoryFile;
    BOOLEAN             OpenTargetDirectory;

    ULONG               CreateDisposition;

    Irp = IrpContext->Irp;
    IrpSp = IoGetCurrentIrpStackLocation(Irp);

    Options  = IrpSp->Parameters.Create.Options;

    DirectoryFile = IsFlagOn(Options, FILE_DIRECTORY_FILE);
    OpenTargetDirectory = IsFlagOn(IrpSp->Flags, SL_OPEN_TARGET_DIRECTORY);

    CreateDisposition = (Options >> 24) & 0x000000ff;

    DesiredAccess = IrpSp->Parameters.Create.SecurityContext->DesiredAccess;
    ShareAccess   = IrpSp->Parameters.Create.ShareAccess;

    if (DirectoryFile) {
        return STATUS_NOT_A_DIRECTORY;
    }

    if (OpenTargetDirectory) {
        DbgBreak();
        return STATUS_INVALID_PARAMETER;
    }

    if ( (CreateDisposition != FILE_OPEN) &&
            (CreateDisposition != FILE_OPEN_IF) ) {
        return STATUS_ACCESS_DENIED;
    }

    if ( !FlagOn(ShareAccess, FILE_SHARE_READ) &&
            Vcb->OpenVolumeCount  != 0 ) {
        return STATUS_SHARING_VIOLATION;
    }

    Ccb = Ext2AllocateCcb(0, NULL);
    if (Ccb == NULL) {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto errorout;
    }

    Status = STATUS_SUCCESS;

    if (Vcb->OpenVolumeCount > 0) {
        Status = IoCheckShareAccess( DesiredAccess, ShareAccess,
                                     IrpSp->FileObject,
                                     &(Vcb->ShareAccess), TRUE);

        if (!NT_SUCCESS(Status)) {
            goto errorout;
        }
    } else {
        IoSetShareAccess( DesiredAccess, ShareAccess,
                          IrpSp->FileObject,
                          &(Vcb->ShareAccess)   );
    }


    if (Vcb->OpenVolumeCount == 0 &&
        !IsFlagOn(ShareAccess, FILE_SHARE_READ)  &&
        !IsFlagOn(ShareAccess, FILE_SHARE_WRITE) ){

        if (!IsVcbReadOnly(Vcb)) {
            Ext2FlushFiles(IrpContext, Vcb, FALSE);
            Ext2FlushVolume(IrpContext, Vcb, FALSE);
        }

        SetLongFlag(Vcb->Flags, VCB_VOLUME_LOCKED);
        Vcb->LockFile = IrpSp->FileObject;
    } else {

        if (FlagOn(IrpSp->FileObject->Flags, FO_NO_INTERMEDIATE_BUFFERING) &&
            FlagOn(DesiredAccess, FILE_READ_DATA | FILE_WRITE_DATA) ) {
            if (!IsVcbReadOnly(Vcb)) {
                Ext2FlushFiles(IrpContext, Vcb, FALSE);
                Ext2FlushVolume(IrpContext, Vcb, FALSE);
            }
        }
    }

    IrpSp->FileObject->Flags |= FO_NO_INTERMEDIATE_BUFFERING;
    IrpSp->FileObject->FsContext  = Vcb;
    IrpSp->FileObject->FsContext2 = Ccb;
    IrpSp->FileObject->Vpb = Vcb->Vpb;

    Ext2ReferXcb(&Vcb->ReferenceCount);
    Ext2ReferXcb(&Vcb->OpenHandleCount);
    Ext2ReferXcb(&Vcb->OpenVolumeCount);

    Irp->IoStatus.Information = FILE_OPENED;

errorout:

    return Status;
}
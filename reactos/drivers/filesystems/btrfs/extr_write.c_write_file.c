#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int Flags2; } ;
struct TYPE_31__ {int /*<<< orphan*/  lock; TYPE_1__ Header; } ;
typedef  TYPE_8__ fcb ;
typedef  int /*<<< orphan*/  device_extension ;
struct TYPE_27__ {int /*<<< orphan*/ * Thread; } ;
struct TYPE_28__ {TYPE_4__ Overlay; } ;
struct TYPE_26__ {void* Information; } ;
struct TYPE_25__ {void* SystemBuffer; } ;
struct TYPE_32__ {int Flags; TYPE_5__ Tail; TYPE_3__ IoStatus; TYPE_2__ AssociatedIrp; scalar_t__ MdlAddress; } ;
struct TYPE_23__ {void* QuadPart; } ;
struct TYPE_29__ {void* Length; TYPE_12__ ByteOffset; } ;
struct TYPE_30__ {TYPE_6__ Write; } ;
struct TYPE_22__ {TYPE_8__* FsContext; } ;
struct TYPE_21__ {TYPE_7__ Parameters; TYPE_11__* FileObject; } ;
typedef  TYPE_9__* PIRP ;
typedef  TYPE_10__* PIO_STACK_LOCATION ;
typedef  TYPE_11__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/ * PETHREAD ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  TYPE_12__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int FSRTL_FLAG2_IS_PAGING_FILE ; 
 int /*<<< orphan*/  FsRtlCheckLockForWriteAccess (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  HighPagePriority ; 
 int IRP_NOCACHE ; 
 int IRP_PAGING_IO ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 TYPE_10__* IoGetCurrentIrpStackLocation (TYPE_9__*) ; 
 TYPE_9__* IoGetTopLevelIrp () ; 
 scalar_t__ IoIsSystemThread (int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NormalPagePriority ; 
 int /*<<< orphan*/ * PsGetCurrentThread () ; 
 int /*<<< orphan*/  PsGetThreadProcess (int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_FILE_LOCK_CONFLICT ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_PENDING ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  clear_rollback (int /*<<< orphan*/ *) ; 
 scalar_t__ diskacc ; 
 int /*<<< orphan*/  do_rollback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fPsUpdateDiskCounters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* map_user_buffer (TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_file2 (int /*<<< orphan*/ *,TYPE_9__*,TYPE_12__,void*,void**,int,int,int,int,int,int /*<<< orphan*/ *) ; 

NTSTATUS write_file(device_extension* Vcb, PIRP Irp, bool wait, bool deferred_write) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    void* buf;
    NTSTATUS Status;
    LARGE_INTEGER offset = IrpSp->Parameters.Write.ByteOffset;
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    fcb* fcb = FileObject ? FileObject->FsContext : NULL;
    LIST_ENTRY rollback;

    InitializeListHead(&rollback);

    TRACE("write\n");

    Irp->IoStatus.Information = 0;

    TRACE("offset = %I64x\n", offset.QuadPart);
    TRACE("length = %x\n", IrpSp->Parameters.Write.Length);

    if (!Irp->AssociatedIrp.SystemBuffer) {
        buf = map_user_buffer(Irp, fcb && fcb->Header.Flags2 & FSRTL_FLAG2_IS_PAGING_FILE ? HighPagePriority : NormalPagePriority);

        if (Irp->MdlAddress && !buf) {
            ERR("MmGetSystemAddressForMdlSafe returned NULL\n");
            Status = STATUS_INSUFFICIENT_RESOURCES;
            goto exit;
        }
    } else
        buf = Irp->AssociatedIrp.SystemBuffer;

    TRACE("buf = %p\n", buf);

    if (fcb && !(Irp->Flags & IRP_PAGING_IO) && !FsRtlCheckLockForWriteAccess(&fcb->lock, Irp)) {
        WARN("tried to write to locked region\n");
        Status = STATUS_FILE_LOCK_CONFLICT;
        goto exit;
    }

    Status = write_file2(Vcb, Irp, offset, buf, &IrpSp->Parameters.Write.Length, Irp->Flags & IRP_PAGING_IO, Irp->Flags & IRP_NOCACHE,
                         wait, deferred_write, true, &rollback);

    if (Status == STATUS_PENDING)
        goto exit;
    else if (!NT_SUCCESS(Status)) {
        ERR("write_file2 returned %08x\n", Status);
        goto exit;
    }

    if (NT_SUCCESS(Status)) {
        Irp->IoStatus.Information = IrpSp->Parameters.Write.Length;

        if (diskacc && Status != STATUS_PENDING && Irp->Flags & IRP_NOCACHE) {
            PETHREAD thread = NULL;

            if (Irp->Tail.Overlay.Thread && !IoIsSystemThread(Irp->Tail.Overlay.Thread))
                thread = Irp->Tail.Overlay.Thread;
            else if (!IoIsSystemThread(PsGetCurrentThread()))
                thread = PsGetCurrentThread();
            else if (IoIsSystemThread(PsGetCurrentThread()) && IoGetTopLevelIrp() == Irp)
                thread = PsGetCurrentThread();

            if (thread)
                fPsUpdateDiskCounters(PsGetThreadProcess(thread), 0, IrpSp->Parameters.Write.Length, 0, 1, 0);
        }
    }

exit:
    if (NT_SUCCESS(Status))
        clear_rollback(&rollback);
    else
        do_rollback(Vcb, &rollback);

    return Status;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  event; scalar_t__ thread; } ;
struct TYPE_12__ {scalar_t__ thread; } ;
struct TYPE_15__ {int locked; int lock_paused_balance; TYPE_3__ balance; int /*<<< orphan*/  locked_fileobj; TYPE_2__* Vpb; int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  readonly; scalar_t__ need_write; int /*<<< orphan*/  fileref_lock; TYPE_7__* root_fileref; TYPE_1__ scrub; } ;
typedef  TYPE_4__ device_extension ;
struct TYPE_17__ {scalar_t__ open_count; scalar_t__ fcb; } ;
struct TYPE_16__ {int /*<<< orphan*/  FileObject; } ;
struct TYPE_13__ {int Flags; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSRTL_VOLUME_LOCK ; 
 int /*<<< orphan*/  FSRTL_VOLUME_LOCK_FAILED ; 
 int /*<<< orphan*/  FsRtlNotifyVolumeEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoAcquireVpbSpinLock (int /*<<< orphan*/ *) ; 
 TYPE_5__* IoGetCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoReleaseVpbSpinLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ KeReadStateEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_DEVICE_NOT_READY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int VPB_LOCKED ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  do_write (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_fcb_caches (TYPE_4__*) ; 
 int /*<<< orphan*/  free_trees (TYPE_4__*) ; 
 scalar_t__ has_open_children (TYPE_7__*) ; 

__attribute__((used)) static NTSTATUS lock_volume(device_extension* Vcb, PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    NTSTATUS Status;
    KIRQL irql;
    bool lock_paused_balance = false;

    TRACE("FSCTL_LOCK_VOLUME\n");

    if (Vcb->scrub.thread) {
        WARN("cannot lock while scrub running\n");
        return STATUS_DEVICE_NOT_READY;
    }

    if (Vcb->balance.thread) {
        WARN("cannot lock while balance running\n");
        return STATUS_DEVICE_NOT_READY;
    }

    TRACE("locking volume\n");

    FsRtlNotifyVolumeEvent(IrpSp->FileObject, FSRTL_VOLUME_LOCK);

    if (Vcb->locked)
        return STATUS_SUCCESS;

    ExAcquireResourceExclusiveLite(&Vcb->fileref_lock, true);

    if (Vcb->root_fileref && Vcb->root_fileref->fcb && (Vcb->root_fileref->open_count > 0 || has_open_children(Vcb->root_fileref))) {
        Status = STATUS_ACCESS_DENIED;
        ExReleaseResourceLite(&Vcb->fileref_lock);
        goto end;
    }

    ExReleaseResourceLite(&Vcb->fileref_lock);

    if (Vcb->balance.thread && KeReadStateEvent(&Vcb->balance.event)) {
        ExAcquireResourceExclusiveLite(&Vcb->tree_lock, true);
        KeClearEvent(&Vcb->balance.event);
        ExReleaseResourceLite(&Vcb->tree_lock);

        lock_paused_balance = true;
    }

    ExAcquireResourceExclusiveLite(&Vcb->tree_lock, true);

    flush_fcb_caches(Vcb);

    if (Vcb->need_write && !Vcb->readonly)
        Status = do_write(Vcb, Irp);
    else
        Status = STATUS_SUCCESS;

    free_trees(Vcb);

    ExReleaseResourceLite(&Vcb->tree_lock);

    if (!NT_SUCCESS(Status)) {
        ERR("do_write returned %08x\n", Status);
        goto end;
    }

    IoAcquireVpbSpinLock(&irql);

    if (!(Vcb->Vpb->Flags & VPB_LOCKED)) {
        Vcb->Vpb->Flags |= VPB_LOCKED;
        Vcb->locked = true;
        Vcb->locked_fileobj = IrpSp->FileObject;
        Vcb->lock_paused_balance = lock_paused_balance;
    } else {
        Status = STATUS_ACCESS_DENIED;
        IoReleaseVpbSpinLock(irql);

        if (lock_paused_balance)
            KeSetEvent(&Vcb->balance.event, 0, false);

        goto end;
    }

    IoReleaseVpbSpinLock(irql);

    Status = STATUS_SUCCESS;

end:
    if (!NT_SUCCESS(Status))
        FsRtlNotifyVolumeEvent(IrpSp->FileObject, FSRTL_VOLUME_LOCK_FAILED);

    return Status;
}
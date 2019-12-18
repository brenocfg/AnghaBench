#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {TYPE_6__* fcb; struct TYPE_27__* parent; } ;
typedef  TYPE_5__ file_ref ;
struct TYPE_26__ {int /*<<< orphan*/ * Resource; } ;
struct TYPE_28__ {TYPE_17__* Vcb; TYPE_4__ Header; scalar_t__ ads; } ;
typedef  TYPE_6__ fcb ;
struct TYPE_29__ {int access; TYPE_5__* fileref; } ;
typedef  TYPE_7__ ccb ;
struct TYPE_24__ {int /*<<< orphan*/  InputBufferLength; } ;
struct TYPE_25__ {TYPE_2__ DeviceIoControl; } ;
struct TYPE_31__ {TYPE_3__ Parameters; TYPE_10__* FileObject; } ;
struct TYPE_23__ {void* SystemBuffer; } ;
struct TYPE_30__ {scalar_t__ RequestorMode; scalar_t__ UserBuffer; TYPE_1__ AssociatedIrp; } ;
struct TYPE_22__ {int /*<<< orphan*/  tree_lock; } ;
struct TYPE_21__ {TYPE_7__* FsContext2; TYPE_6__* FsContext; } ;
typedef  int /*<<< orphan*/  REPARSE_DATA_BUFFER ;
typedef  TYPE_8__* PIRP ;
typedef  TYPE_9__* PIO_STACK_LOCATION ;
typedef  TYPE_10__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ACTION_MODIFIED ; 
 int FILE_NOTIFY_CHANGE_ATTRIBUTES ; 
 int FILE_NOTIFY_CHANGE_LAST_WRITE ; 
 int FILE_WRITE_ATTRIBUTES ; 
 int FILE_WRITE_DATA ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 TYPE_9__* IoGetCurrentIrpStackLocation (TYPE_8__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ UserMode ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  clear_rollback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_rollback (TYPE_17__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_notification_fcb (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_reparse_point2 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*,TYPE_5__*,TYPE_8__*,int /*<<< orphan*/ *) ; 

NTSTATUS set_reparse_point(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    void* buffer = Irp->AssociatedIrp.SystemBuffer;
    REPARSE_DATA_BUFFER* rdb = buffer;
    DWORD buflen = IrpSp->Parameters.DeviceIoControl.InputBufferLength;
    NTSTATUS Status = STATUS_SUCCESS;
    fcb* fcb;
    ccb* ccb;
    file_ref* fileref;
    LIST_ENTRY rollback;

    TRACE("(%p, %p)\n", DeviceObject, Irp);

    InitializeListHead(&rollback);

    if (!FileObject) {
        ERR("FileObject was NULL\n");
        return STATUS_INVALID_PARAMETER;
    }

    // IFSTest insists on this, for some reason...
    if (Irp->UserBuffer)
        return STATUS_INVALID_PARAMETER;

    fcb = FileObject->FsContext;
    ccb = FileObject->FsContext2;

    if (!ccb) {
        ERR("ccb was NULL\n");
        return STATUS_INVALID_PARAMETER;
    }

    if (Irp->RequestorMode == UserMode && !(ccb->access & (FILE_WRITE_ATTRIBUTES | FILE_WRITE_DATA))) {
        WARN("insufficient privileges\n");
        return STATUS_ACCESS_DENIED;
    }

    fileref = ccb->fileref;

    if (!fileref) {
        ERR("fileref was NULL\n");
        return STATUS_INVALID_PARAMETER;
    }

    if (fcb->ads) {
        fileref = fileref->parent;
        fcb = fileref->fcb;
    }

    ExAcquireResourceSharedLite(&fcb->Vcb->tree_lock, true);
    ExAcquireResourceExclusiveLite(fcb->Header.Resource, true);

    Status = set_reparse_point2(fcb, rdb, buflen, ccb, fileref, Irp, &rollback);
    if (!NT_SUCCESS(Status)) {
        ERR("set_reparse_point2 returned %08x\n", Status);
        goto end;
    }

    queue_notification_fcb(fileref, FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_ATTRIBUTES, FILE_ACTION_MODIFIED, NULL);

end:
    if (NT_SUCCESS(Status))
        clear_rollback(&rollback);
    else
        do_rollback(fcb->Vcb, &rollback);

    ExReleaseResourceLite(fcb->Header.Resource);
    ExReleaseResourceLite(&fcb->Vcb->tree_lock);

    return Status;
}
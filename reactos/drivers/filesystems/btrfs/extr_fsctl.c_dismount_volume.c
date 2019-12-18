#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ page_file_count; int removing; int /*<<< orphan*/  tree_lock; TYPE_2__* vde; int /*<<< orphan*/  open_files; int /*<<< orphan*/  readonly; scalar_t__ need_write; int /*<<< orphan*/  locked; int /*<<< orphan*/  root_file; scalar_t__ disallow_dismount; TYPE_1__* Vpb; } ;
typedef  TYPE_3__ device_extension ;
struct TYPE_11__ {int /*<<< orphan*/ * mounted_device; } ;
struct TYPE_10__ {int Flags; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FSRTL_VOLUME_DISMOUNT ; 
 int /*<<< orphan*/  FsRtlNotifyVolumeEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int VPB_MOUNTED ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  do_write (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_fcb_caches (TYPE_3__*) ; 
 int /*<<< orphan*/  free_trees (TYPE_3__*) ; 
 int /*<<< orphan*/  uninit (TYPE_3__*) ; 
 int /*<<< orphan*/  update_volumes (TYPE_3__*) ; 

NTSTATUS dismount_volume(device_extension* Vcb, bool shutdown, PIRP Irp) {
    NTSTATUS Status;
    bool open_files;

    TRACE("FSCTL_DISMOUNT_VOLUME\n");

    if (!(Vcb->Vpb->Flags & VPB_MOUNTED))
        return STATUS_SUCCESS;

    if (!shutdown) {
        if (Vcb->disallow_dismount || Vcb->page_file_count != 0) {
            WARN("attempting to dismount boot volume or one containing a pagefile\n");
            return STATUS_ACCESS_DENIED;
        }

        Status = FsRtlNotifyVolumeEvent(Vcb->root_file, FSRTL_VOLUME_DISMOUNT);
        if (!NT_SUCCESS(Status)) {
            WARN("FsRtlNotifyVolumeEvent returned %08x\n", Status);
        }
    }

    ExAcquireResourceExclusiveLite(&Vcb->tree_lock, true);

    if (!Vcb->locked) {
        flush_fcb_caches(Vcb);

        if (Vcb->need_write && !Vcb->readonly) {
            Status = do_write(Vcb, Irp);

            if (!NT_SUCCESS(Status))
                ERR("do_write returned %08x\n", Status);
        }
    }

    free_trees(Vcb);

    Vcb->removing = true;

    open_files = Vcb->open_files > 0;

    if (Vcb->vde) {
        update_volumes(Vcb);
        Vcb->vde->mounted_device = NULL;
    }

    ExReleaseResourceLite(&Vcb->tree_lock);

    if (!open_files)
        uninit(Vcb);

    return STATUS_SUCCESS;
}
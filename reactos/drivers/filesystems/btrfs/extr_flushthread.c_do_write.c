#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int readonly; int /*<<< orphan*/  root_file; } ;
typedef  TYPE_1__ device_extension ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSRTL_VOLUME_FORCED_CLOSED ; 
 int /*<<< orphan*/  FsRtlNotifyVolumeEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_rollback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_rollback (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_write2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

NTSTATUS do_write(device_extension* Vcb, PIRP Irp) {
    LIST_ENTRY rollback;
    NTSTATUS Status;

    InitializeListHead(&rollback);

    Status = do_write2(Vcb, Irp, &rollback);

    if (!NT_SUCCESS(Status)) {
        ERR("do_write2 returned %08x, dropping into readonly mode\n", Status);
        Vcb->readonly = true;
        FsRtlNotifyVolumeEvent(Vcb->root_file, FSRTL_VOLUME_FORCED_CLOSED);
        do_rollback(Vcb, &rollback);
    } else
        clear_rollback(&rollback);

    return Status;
}
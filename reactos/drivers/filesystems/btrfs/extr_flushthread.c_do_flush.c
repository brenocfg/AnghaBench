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
struct TYPE_5__ {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  readonly; scalar_t__ need_write; } ;
typedef  TYPE_1__ device_extension ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  do_write (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_trees (TYPE_1__*) ; 

__attribute__((used)) static void do_flush(device_extension* Vcb) {
    NTSTATUS Status;

    ExAcquireResourceExclusiveLite(&Vcb->tree_lock, true);

    if (Vcb->need_write && !Vcb->readonly)
        Status = do_write(Vcb, NULL);
    else
        Status = STATUS_SUCCESS;

    free_trees(Vcb);

    if (!NT_SUCCESS(Status))
        ERR("do_write returned %08x\n", Status);

    ExReleaseResourceLite(&Vcb->tree_lock);
}
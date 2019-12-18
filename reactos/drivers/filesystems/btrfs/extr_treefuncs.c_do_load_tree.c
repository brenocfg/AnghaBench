#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_22__ {TYPE_4__* tree; int /*<<< orphan*/  generation; int /*<<< orphan*/  address; } ;
typedef  TYPE_5__ tree_holder ;
typedef  int /*<<< orphan*/  tree_data ;
struct TYPE_23__ {TYPE_2__* nonpaged; } ;
typedef  TYPE_6__ tree ;
struct TYPE_24__ {TYPE_3__* nonpaged; } ;
typedef  TYPE_7__ root ;
struct TYPE_18__ {int /*<<< orphan*/  node_size; } ;
struct TYPE_25__ {TYPE_1__ superblock; } ;
typedef  TYPE_8__ device_extension ;
typedef  int /*<<< orphan*/  chunk ;
struct TYPE_21__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_20__ {int /*<<< orphan*/  load_tree_lock; } ;
struct TYPE_19__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ExAcquireFastMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExReleaseFastMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NormalPagePriority ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  do_load_tree2 (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_data (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

NTSTATUS do_load_tree(device_extension* Vcb, tree_holder* th, root* r, tree* t, tree_data* td, PIRP Irp) {
    NTSTATUS Status;
    uint8_t* buf;
    chunk* c;

    buf = ExAllocatePoolWithTag(PagedPool, Vcb->superblock.node_size, ALLOC_TAG);
    if (!buf) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = read_data(Vcb, th->address, Vcb->superblock.node_size, NULL, true, buf, NULL,
                       &c, Irp, th->generation, false, NormalPagePriority);
    if (!NT_SUCCESS(Status)) {
        ERR("read_data returned 0x%08x\n", Status);
        ExFreePool(buf);
        return Status;
    }

    if (t)
        ExAcquireFastMutex(&t->nonpaged->mutex);
    else
        ExAcquireResourceExclusiveLite(&r->nonpaged->load_tree_lock, true);

    Status = do_load_tree2(Vcb, th, buf, r, t, td);

    if (t)
        ExReleaseFastMutex(&t->nonpaged->mutex);
    else
        ExReleaseResourceLite(&r->nonpaged->load_tree_lock);

    if (!th->tree || th->tree->buf != buf)
        ExFreePool(buf);

    if (!NT_SUCCESS(Status)) {
        ERR("do_load_tree2 returned %08x\n", Status);
        return Status;
    }

    return Status;
}
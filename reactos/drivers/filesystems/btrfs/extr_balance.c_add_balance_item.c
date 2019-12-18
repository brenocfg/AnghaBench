#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_1__* item; } ;
typedef  TYPE_3__ traverse_ptr ;
struct TYPE_24__ {TYPE_17__* opts; } ;
struct TYPE_26__ {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  root_root; TYPE_2__ balance; } ;
typedef  TYPE_4__ device_extension ;
struct TYPE_28__ {int /*<<< orphan*/  system; int /*<<< orphan*/  flags; int /*<<< orphan*/  metadata; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {scalar_t__ offset; int /*<<< orphan*/  obj_type; int /*<<< orphan*/  obj_id; } ;
struct TYPE_23__ {int /*<<< orphan*/  key; } ;
struct TYPE_22__ {int flags; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_5__ KEY ;
typedef  TYPE_6__ BALANCE_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  BALANCE_FLAGS_DATA ; 
 int /*<<< orphan*/  BALANCE_FLAGS_METADATA ; 
 int /*<<< orphan*/  BALANCE_FLAGS_SYSTEM ; 
 int /*<<< orphan*/  BALANCE_ITEM_ID ; 
 size_t BALANCE_OPTS_DATA ; 
 size_t BALANCE_OPTS_METADATA ; 
 size_t BALANCE_OPTS_SYSTEM ; 
 int BTRFS_BALANCE_OPTS_ENABLED ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 TYPE_6__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_6__*) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_6__*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TYPE_TEMP_ITEM ; 
 int /*<<< orphan*/  copy_balance_args (TYPE_17__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_tree_item (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  do_write (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_item (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_trees (TYPE_4__*) ; 
 int /*<<< orphan*/  insert_tree_item (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keycmp (int /*<<< orphan*/ ,TYPE_5__) ; 

__attribute__((used)) static NTSTATUS add_balance_item(device_extension* Vcb) {
    KEY searchkey;
    traverse_ptr tp;
    NTSTATUS Status;
    BALANCE_ITEM* bi;

    searchkey.obj_id = BALANCE_ITEM_ID;
    searchkey.obj_type = TYPE_TEMP_ITEM;
    searchkey.offset = 0;

    ExAcquireResourceExclusiveLite(&Vcb->tree_lock, true);

    Status = find_item(Vcb, Vcb->root_root, &tp, &searchkey, false, NULL);
    if (!NT_SUCCESS(Status)) {
        ERR("find_item returned %08x\n", Status);
        goto end;
    }

    if (!keycmp(tp.item->key, searchkey)) {
        Status = delete_tree_item(Vcb, &tp);
        if (!NT_SUCCESS(Status)) {
            ERR("delete_tree_item returned %08x\n", Status);
            goto end;
        }
    }

    bi = ExAllocatePoolWithTag(PagedPool, sizeof(BALANCE_ITEM), ALLOC_TAG);
    if (!bi) {
        ERR("out of memory\n");
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto end;
    }

    RtlZeroMemory(bi, sizeof(BALANCE_ITEM));

    if (Vcb->balance.opts[BALANCE_OPTS_DATA].flags & BTRFS_BALANCE_OPTS_ENABLED) {
        bi->flags |= BALANCE_FLAGS_DATA;
        copy_balance_args(&Vcb->balance.opts[BALANCE_OPTS_DATA], &bi->data);
    }

    if (Vcb->balance.opts[BALANCE_OPTS_METADATA].flags & BTRFS_BALANCE_OPTS_ENABLED) {
        bi->flags |= BALANCE_FLAGS_METADATA;
        copy_balance_args(&Vcb->balance.opts[BALANCE_OPTS_METADATA], &bi->metadata);
    }

    if (Vcb->balance.opts[BALANCE_OPTS_SYSTEM].flags & BTRFS_BALANCE_OPTS_ENABLED) {
        bi->flags |= BALANCE_FLAGS_SYSTEM;
        copy_balance_args(&Vcb->balance.opts[BALANCE_OPTS_SYSTEM], &bi->system);
    }

    Status = insert_tree_item(Vcb, Vcb->root_root, BALANCE_ITEM_ID, TYPE_TEMP_ITEM, 0, bi, sizeof(BALANCE_ITEM), NULL, NULL);
    if (!NT_SUCCESS(Status)) {
        ERR("insert_tree_item returned %08x\n", Status);
        ExFreePool(bi);
        goto end;
    }

    Status = STATUS_SUCCESS;

end:
    if (NT_SUCCESS(Status)) {
        Status = do_write(Vcb, NULL);
        if (!NT_SUCCESS(Status))
            ERR("do_write returned %08x\n", Status);
    }

    free_trees(Vcb);

    ExReleaseResourceLite(&Vcb->tree_lock);

    return Status;
}
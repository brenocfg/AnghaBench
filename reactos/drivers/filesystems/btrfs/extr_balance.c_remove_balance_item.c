#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* item; } ;
typedef  TYPE_2__ traverse_ptr ;
struct TYPE_16__ {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  root_root; } ;
typedef  TYPE_3__ device_extension ;
struct TYPE_17__ {scalar_t__ offset; int /*<<< orphan*/  obj_type; int /*<<< orphan*/  obj_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BALANCE_ITEM_ID ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TYPE_TEMP_ITEM ; 
 int /*<<< orphan*/  delete_tree_item (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  do_write (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_item (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_trees (TYPE_3__*) ; 
 int /*<<< orphan*/  keycmp (int /*<<< orphan*/ ,TYPE_4__) ; 

__attribute__((used)) static NTSTATUS remove_balance_item(device_extension* Vcb) {
    KEY searchkey;
    traverse_ptr tp;
    NTSTATUS Status;

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

        Status = do_write(Vcb, NULL);
        if (!NT_SUCCESS(Status)) {
            ERR("do_write returned %08x\n", Status);
            goto end;
        }

        free_trees(Vcb);
    }

    Status = STATUS_SUCCESS;

end:
    ExReleaseResourceLite(&Vcb->tree_lock);

    return Status;
}
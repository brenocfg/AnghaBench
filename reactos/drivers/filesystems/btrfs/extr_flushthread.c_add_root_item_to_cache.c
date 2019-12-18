#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_17__ {TYPE_3__* tree; TYPE_2__* item; } ;
typedef  TYPE_4__ traverse_ptr ;
struct TYPE_18__ {int /*<<< orphan*/  root_root; } ;
typedef  TYPE_5__ device_extension ;
struct TYPE_19__ {scalar_t__ obj_id; scalar_t__ obj_type; int offset; } ;
struct TYPE_16__ {int write; } ;
struct TYPE_14__ {scalar_t__ obj_id; scalar_t__ obj_type; int /*<<< orphan*/  offset; } ;
struct TYPE_15__ {int size; TYPE_1__ key; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  ROOT_ITEM ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_6__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_INTERNAL_ERROR ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ TYPE_ROOT_ITEM ; 
 scalar_t__ delete_tree_item (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ find_item (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ insert_tree_item (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS add_root_item_to_cache(device_extension* Vcb, uint64_t root, PIRP Irp) {
    KEY searchkey;
    traverse_ptr tp;
    NTSTATUS Status;

    searchkey.obj_id = root;
    searchkey.obj_type = TYPE_ROOT_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->root_root, &tp, &searchkey, false, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);
        return Status;
    }

    if (tp.item->key.obj_id != searchkey.obj_id || tp.item->key.obj_type != searchkey.obj_type) {
        ERR("could not find ROOT_ITEM for tree %I64x\n", searchkey.obj_id);
        return STATUS_INTERNAL_ERROR;
    }

    if (tp.item->size < sizeof(ROOT_ITEM)) { // if not full length, create new entry with new bits zeroed
        ROOT_ITEM* ri = ExAllocatePoolWithTag(PagedPool, sizeof(ROOT_ITEM), ALLOC_TAG);
        if (!ri) {
            ERR("out of memory\n");
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        if (tp.item->size > 0)
            RtlCopyMemory(ri, tp.item->data, tp.item->size);

        RtlZeroMemory(((uint8_t*)ri) + tp.item->size, sizeof(ROOT_ITEM) - tp.item->size);

        Status = delete_tree_item(Vcb, &tp);
        if (!NT_SUCCESS(Status)) {
            ERR("delete_tree_item returned %08x\n", Status);
            ExFreePool(ri);
            return Status;
        }

        Status = insert_tree_item(Vcb, Vcb->root_root, searchkey.obj_id, searchkey.obj_type, tp.item->key.offset, ri, sizeof(ROOT_ITEM), NULL, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("insert_tree_item returned %08x\n", Status);
            ExFreePool(ri);
            return Status;
        }
    } else {
        tp.tree->write = true;
    }

    return STATUS_SUCCESS;
}
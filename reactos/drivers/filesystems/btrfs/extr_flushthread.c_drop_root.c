#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_28__ {TYPE_4__* item; } ;
typedef  TYPE_5__ traverse_ptr ;
struct TYPE_25__ {scalar_t__* uuid; } ;
struct TYPE_24__ {scalar_t__* uuid; } ;
struct TYPE_26__ {scalar_t__ rtransid; TYPE_2__ received_uuid; TYPE_1__ uuid; int /*<<< orphan*/  root_level; } ;
struct TYPE_29__ {scalar_t__ id; TYPE_3__ root_item; int /*<<< orphan*/  treeholder; } ;
typedef  TYPE_6__ root ;
struct TYPE_30__ {scalar_t__ root_root; scalar_t__ uuid_root; } ;
typedef  TYPE_7__ device_extension ;
typedef  int ULONG ;
struct TYPE_31__ {scalar_t__ obj_id; scalar_t__ obj_type; scalar_t__ offset; } ;
struct TYPE_23__ {scalar_t__ obj_id; scalar_t__ obj_type; int /*<<< orphan*/  offset; } ;
struct TYPE_27__ {int size; TYPE_11__ key; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  TYPE_8__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (scalar_t__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ TYPE_ROOT_ITEM ; 
 scalar_t__ TYPE_SUBVOL_REC_UUID ; 
 scalar_t__ TYPE_SUBVOL_UUID ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__,...) ; 
 scalar_t__ delete_tree_item (TYPE_7__*,TYPE_5__*) ; 
 scalar_t__ find_item (TYPE_7__*,scalar_t__,TYPE_5__*,TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_trees_root (TYPE_7__*,TYPE_6__*) ; 
 scalar_t__ insert_tree_item (TYPE_7__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keycmp (TYPE_11__,TYPE_8__) ; 
 scalar_t__ remove_root_extents (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS drop_root(device_extension* Vcb, root* r, PIRP Irp, LIST_ENTRY* rollback) {
    NTSTATUS Status;
    KEY searchkey;
    traverse_ptr tp;

    Status = remove_root_extents(Vcb, r, &r->treeholder, r->root_item.root_level, NULL, Irp, rollback);
    if (!NT_SUCCESS(Status)) {
        ERR("remove_root_extents returned %08x\n", Status);
        return Status;
    }

    // remove entries in uuid root (tree 9)
    if (Vcb->uuid_root) {
        RtlCopyMemory(&searchkey.obj_id, &r->root_item.uuid.uuid[0], sizeof(uint64_t));
        searchkey.obj_type = TYPE_SUBVOL_UUID;
        RtlCopyMemory(&searchkey.offset, &r->root_item.uuid.uuid[sizeof(uint64_t)], sizeof(uint64_t));

        if (searchkey.obj_id != 0 || searchkey.offset != 0) {
            Status = find_item(Vcb, Vcb->uuid_root, &tp, &searchkey, false, Irp);
            if (!NT_SUCCESS(Status)) {
                WARN("find_item returned %08x\n", Status);
            } else {
                if (!keycmp(tp.item->key, searchkey)) {
                    Status = delete_tree_item(Vcb, &tp);
                    if (!NT_SUCCESS(Status)) {
                        ERR("delete_tree_item returned %08x\n", Status);
                        return Status;
                    }
                } else
                    WARN("could not find (%I64x,%x,%I64x) in uuid tree\n", searchkey.obj_id, searchkey.obj_type, searchkey.offset);
            }
        }

        if (r->root_item.rtransid > 0) {
            RtlCopyMemory(&searchkey.obj_id, &r->root_item.received_uuid.uuid[0], sizeof(uint64_t));
            searchkey.obj_type = TYPE_SUBVOL_REC_UUID;
            RtlCopyMemory(&searchkey.offset, &r->root_item.received_uuid.uuid[sizeof(uint64_t)], sizeof(uint64_t));

            Status = find_item(Vcb, Vcb->uuid_root, &tp, &searchkey, false, Irp);
            if (!NT_SUCCESS(Status))
                WARN("find_item returned %08x\n", Status);
            else {
                if (!keycmp(tp.item->key, searchkey)) {
                    if (tp.item->size == sizeof(uint64_t)) {
                        uint64_t* id = (uint64_t*)tp.item->data;

                        if (*id == r->id) {
                            Status = delete_tree_item(Vcb, &tp);
                            if (!NT_SUCCESS(Status)) {
                                ERR("delete_tree_item returned %08x\n", Status);
                                return Status;
                            }
                        }
                    } else if (tp.item->size > sizeof(uint64_t)) {
                        ULONG i;
                        uint64_t* ids = (uint64_t*)tp.item->data;

                        for (i = 0; i < tp.item->size / sizeof(uint64_t); i++) {
                            if (ids[i] == r->id) {
                                uint64_t* ne;

                                ne = ExAllocatePoolWithTag(PagedPool, tp.item->size - sizeof(uint64_t), ALLOC_TAG);
                                if (!ne) {
                                    ERR("out of memory\n");
                                    return STATUS_INSUFFICIENT_RESOURCES;
                                }

                                if (i > 0)
                                    RtlCopyMemory(ne, ids, sizeof(uint64_t) * i);

                                if ((i + 1) * sizeof(uint64_t) < tp.item->size)
                                    RtlCopyMemory(&ne[i], &ids[i + 1], tp.item->size - ((i + 1) * sizeof(uint64_t)));

                                Status = delete_tree_item(Vcb, &tp);
                                if (!NT_SUCCESS(Status)) {
                                    ERR("delete_tree_item returned %08x\n", Status);
                                    ExFreePool(ne);
                                    return Status;
                                }

                                Status = insert_tree_item(Vcb, Vcb->uuid_root, tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset,
                                                          ne, tp.item->size - sizeof(uint64_t), NULL, Irp);
                                if (!NT_SUCCESS(Status)) {
                                    ERR("insert_tree_item returned %08x\n", Status);
                                    ExFreePool(ne);
                                    return Status;
                                }

                                break;
                            }
                        }
                    }
                } else
                    WARN("could not find (%I64x,%x,%I64x) in uuid tree\n", searchkey.obj_id, searchkey.obj_type, searchkey.offset);
            }
        }
    }

    // delete ROOT_ITEM

    searchkey.obj_id = r->id;
    searchkey.obj_type = TYPE_ROOT_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->root_root, &tp, &searchkey, false, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("find_item returned %08x\n", Status);
        return Status;
    }

    if (tp.item->key.obj_id == searchkey.obj_id && tp.item->key.obj_type == searchkey.obj_type) {
        Status = delete_tree_item(Vcb, &tp);

        if (!NT_SUCCESS(Status)) {
            ERR("delete_tree_item returned %08x\n", Status);
            return Status;
        }
    } else
        WARN("could not find (%I64x,%x,%I64x) in root_root\n", searchkey.obj_id, searchkey.obj_type, searchkey.offset);

    // delete items in tree cache

    free_trees_root(Vcb, r);

    return STATUS_SUCCESS;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_21__ {TYPE_2__* item; } ;
typedef  TYPE_3__ traverse_ptr ;
struct TYPE_22__ {int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_4__ device_extension ;
struct TYPE_24__ {int /*<<< orphan*/  count; int /*<<< orphan*/  root; } ;
struct TYPE_23__ {scalar_t__ obj_id; scalar_t__ obj_type; int offset; } ;
struct TYPE_19__ {scalar_t__ obj_id; scalar_t__ obj_type; scalar_t__ offset; } ;
struct TYPE_20__ {int size; TYPE_1__ key; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  TYPE_5__ KEY ;
typedef  TYPE_6__ EXTENT_REF_V0 ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int EXTENT_ITEM_DATA ; 
 int EXTENT_ITEM_SHARED_BACKREFS ; 
 int EXTENT_ITEM_TREE_BLOCK ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ STATUS_INTERNAL_ERROR ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 scalar_t__ TYPE_EXTENT_REF_V0 ; 
 scalar_t__ add_shared_block_extent_ref (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ add_shared_data_extent_ref (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ add_tree_block_extent_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ construct_extent_item (TYPE_4__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ delete_tree_item (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ find_item (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ find_next_item (TYPE_4__*,TYPE_3__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_refs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS convert_old_extent(device_extension* Vcb, uint64_t address, bool tree, KEY* firstitem, uint8_t level, PIRP Irp) {
    NTSTATUS Status;
    KEY searchkey;
    traverse_ptr tp, next_tp;
    LIST_ENTRY extent_refs;
    uint64_t size;

    InitializeListHead(&extent_refs);

    searchkey.obj_id = address;
    searchkey.obj_type = TYPE_EXTENT_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, false, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("find_item returned %08x\n", Status);
        return Status;
    }

    if (tp.item->key.obj_id != searchkey.obj_id || tp.item->key.obj_type != searchkey.obj_type) {
        ERR("old-style extent %I64x not found\n", address);
        return STATUS_INTERNAL_ERROR;
    }

    size = tp.item->key.offset;

    Status = delete_tree_item(Vcb, &tp);
    if (!NT_SUCCESS(Status)) {
        ERR("delete_tree_item returned %08x\n", Status);
        return Status;
    }

    while (find_next_item(Vcb, &tp, &next_tp, false, Irp)) {
        tp = next_tp;

        if (tp.item->key.obj_id == address && tp.item->key.obj_type == TYPE_EXTENT_REF_V0 && tp.item->size >= sizeof(EXTENT_REF_V0)) {
            EXTENT_REF_V0* erv0 = (EXTENT_REF_V0*)tp.item->data;

            if (tree) {
                if (tp.item->key.offset == tp.item->key.obj_id) { // top of the tree
                    Status = add_tree_block_extent_ref(&extent_refs, erv0->root);
                    if (!NT_SUCCESS(Status)) {
                        ERR("add_tree_block_extent_ref returned %08x\n", Status);
                        goto end;
                    }
                } else {
                    Status = add_shared_block_extent_ref(&extent_refs, tp.item->key.offset);
                    if (!NT_SUCCESS(Status)) {
                        ERR("add_shared_block_extent_ref returned %08x\n", Status);
                        goto end;
                    }
                }
            } else {
                Status = add_shared_data_extent_ref(&extent_refs, tp.item->key.offset, erv0->count);
                if (!NT_SUCCESS(Status)) {
                    ERR("add_shared_data_extent_ref returned %08x\n", Status);
                    goto end;
                }
            }

            Status = delete_tree_item(Vcb, &tp);
            if (!NT_SUCCESS(Status)) {
                ERR("delete_tree_item returned %08x\n", Status);
                goto end;
            }
        }

        if (tp.item->key.obj_id > address || tp.item->key.obj_type > TYPE_EXTENT_REF_V0)
            break;
    }

    Status = construct_extent_item(Vcb, address, size, tree ? (EXTENT_ITEM_TREE_BLOCK | EXTENT_ITEM_SHARED_BACKREFS) : EXTENT_ITEM_DATA,
                                   &extent_refs, firstitem, level, Irp);
    if (!NT_SUCCESS(Status))
        ERR("construct_extent_item returned %08x\n", Status);

end:
    free_extent_refs(&extent_refs);

    return Status;
}
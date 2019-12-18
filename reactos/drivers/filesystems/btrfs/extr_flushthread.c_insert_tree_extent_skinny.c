#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_18__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_4__ traverse_ptr ;
struct TYPE_17__ {int /*<<< orphan*/  node_size; int /*<<< orphan*/  generation; } ;
struct TYPE_19__ {TYPE_3__ superblock; int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_5__ device_extension ;
typedef  int /*<<< orphan*/  chunk ;
struct TYPE_16__ {int /*<<< orphan*/  offset; } ;
struct TYPE_15__ {int refcount; int /*<<< orphan*/  flags; int /*<<< orphan*/  generation; } ;
struct TYPE_20__ {TYPE_2__ tbr; int /*<<< orphan*/  type; TYPE_1__ ei; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  TYPE_6__ EXTENT_ITEM_SKINNY_METADATA ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  EXTENT_ITEM_TREE_BLOCK ; 
 TYPE_6__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_6__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  TYPE_METADATA_ITEM ; 
 int /*<<< orphan*/  TYPE_TREE_BLOCK_REF ; 
 int /*<<< orphan*/  acquire_chunk_lock (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  add_parents_to_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_tree_item (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_chunk_lock (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  space_list_subtract (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool insert_tree_extent_skinny(device_extension* Vcb, uint8_t level, uint64_t root_id, chunk* c, uint64_t address, PIRP Irp, LIST_ENTRY* rollback) {
    NTSTATUS Status;
    EXTENT_ITEM_SKINNY_METADATA* eism;
    traverse_ptr insert_tp;

    eism = ExAllocatePoolWithTag(PagedPool, sizeof(EXTENT_ITEM_SKINNY_METADATA), ALLOC_TAG);
    if (!eism) {
        ERR("out of memory\n");
        return false;
    }

    eism->ei.refcount = 1;
    eism->ei.generation = Vcb->superblock.generation;
    eism->ei.flags = EXTENT_ITEM_TREE_BLOCK;
    eism->type = TYPE_TREE_BLOCK_REF;
    eism->tbr.offset = root_id;

    Status = insert_tree_item(Vcb, Vcb->extent_root, address, TYPE_METADATA_ITEM, level, eism, sizeof(EXTENT_ITEM_SKINNY_METADATA), &insert_tp, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("insert_tree_item returned %08x\n", Status);
        ExFreePool(eism);
        return false;
    }

    acquire_chunk_lock(c, Vcb);

    space_list_subtract(c, false, address, Vcb->superblock.node_size, rollback);

    release_chunk_lock(c, Vcb);

    add_parents_to_cache(insert_tp.tree);

    return true;
}
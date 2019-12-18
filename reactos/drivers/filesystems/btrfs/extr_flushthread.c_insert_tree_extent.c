#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_23__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_5__ traverse_ptr ;
struct TYPE_22__ {int incompat_flags; int /*<<< orphan*/  node_size; int /*<<< orphan*/  generation; } ;
struct TYPE_24__ {TYPE_4__ superblock; int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_6__ device_extension ;
typedef  int /*<<< orphan*/  chunk ;
struct TYPE_21__ {int /*<<< orphan*/  offset; } ;
struct TYPE_19__ {int refcount; int /*<<< orphan*/  flags; int /*<<< orphan*/  generation; } ;
struct TYPE_20__ {int /*<<< orphan*/  level; TYPE_1__ extent_item; } ;
struct TYPE_25__ {TYPE_3__ tbr; int /*<<< orphan*/  type; TYPE_2__ eit; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;
typedef  TYPE_7__ EXTENT_ITEM_TREE2 ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  EXTENT_ITEM_TREE_BLOCK ; 
 TYPE_7__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_7__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_EXTENT_ITEM ; 
 int /*<<< orphan*/  TYPE_TREE_BLOCK_REF ; 
 int /*<<< orphan*/  acquire_chunk_lock (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  add_parents_to_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_metadata_address_in_chunk (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int insert_tree_extent_skinny (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_tree_item (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_chunk_lock (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  space_list_subtract (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool insert_tree_extent(device_extension* Vcb, uint8_t level, uint64_t root_id, chunk* c, uint64_t* new_address, PIRP Irp, LIST_ENTRY* rollback) {
    NTSTATUS Status;
    uint64_t address;
    EXTENT_ITEM_TREE2* eit2;
    traverse_ptr insert_tp;

    TRACE("(%p, %x, %I64x, %p, %p, %p, %p)\n", Vcb, level, root_id, c, new_address, rollback);

    if (!find_metadata_address_in_chunk(Vcb, c, &address))
        return false;

    if (Vcb->superblock.incompat_flags & BTRFS_INCOMPAT_FLAGS_SKINNY_METADATA) {
        bool b = insert_tree_extent_skinny(Vcb, level, root_id, c, address, Irp, rollback);

        if (b)
            *new_address = address;

        return b;
    }

    eit2 = ExAllocatePoolWithTag(PagedPool, sizeof(EXTENT_ITEM_TREE2), ALLOC_TAG);
    if (!eit2) {
        ERR("out of memory\n");
        return false;
    }

    eit2->eit.extent_item.refcount = 1;
    eit2->eit.extent_item.generation = Vcb->superblock.generation;
    eit2->eit.extent_item.flags = EXTENT_ITEM_TREE_BLOCK;
    eit2->eit.level = level;
    eit2->type = TYPE_TREE_BLOCK_REF;
    eit2->tbr.offset = root_id;

    Status = insert_tree_item(Vcb, Vcb->extent_root, address, TYPE_EXTENT_ITEM, Vcb->superblock.node_size, eit2, sizeof(EXTENT_ITEM_TREE2), &insert_tp, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("insert_tree_item returned %08x\n", Status);
        ExFreePool(eit2);
        return false;
    }

    acquire_chunk_lock(c, Vcb);

    space_list_subtract(c, false, address, Vcb->superblock.node_size, rollback);

    release_chunk_lock(c, Vcb);

    add_parents_to_cache(insert_tp.tree);

    *new_address = address;

    return true;
}
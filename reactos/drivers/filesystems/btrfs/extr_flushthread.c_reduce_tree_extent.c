#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct TYPE_21__ {int tree_id; } ;
struct TYPE_23__ {TYPE_1__ header; scalar_t__ parent; } ;
typedef  TYPE_3__ tree ;
struct TYPE_22__ {int /*<<< orphan*/  node_size; } ;
struct TYPE_24__ {TYPE_2__ superblock; } ;
typedef  TYPE_4__ device_extension ;
struct TYPE_25__ {int /*<<< orphan*/  used; int /*<<< orphan*/  cache_loaded; } ;
typedef  TYPE_5__ chunk ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int) ; 
 int STATUS_INTERNAL_ERROR ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  acquire_chunk_lock (TYPE_5__*,TYPE_4__*) ; 
 int decrease_extent_refcount_tree (TYPE_4__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* get_chunk_from_address (TYPE_4__*,int) ; 
 int get_extent_refcount (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int load_cache_chunk (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_chunk_lock (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  space_list_add (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS reduce_tree_extent(device_extension* Vcb, uint64_t address, tree* t, uint64_t parent_root, uint8_t level, PIRP Irp, LIST_ENTRY* rollback) {
    NTSTATUS Status;
    uint64_t rc, root;

    TRACE("(%p, %I64x, %p)\n", Vcb, address, t);

    rc = get_extent_refcount(Vcb, address, Vcb->superblock.node_size, Irp);
    if (rc == 0) {
        ERR("error - refcount for extent %I64x was 0\n", address);
        return STATUS_INTERNAL_ERROR;
    }

    if (!t || t->parent)
        root = parent_root;
    else
        root = t->header.tree_id;

    Status = decrease_extent_refcount_tree(Vcb, address, Vcb->superblock.node_size, root, level, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("decrease_extent_refcount_tree returned %08x\n", Status);
        return Status;
    }

    if (rc == 1) {
        chunk* c = get_chunk_from_address(Vcb, address);

        if (c) {
            acquire_chunk_lock(c, Vcb);

            if (!c->cache_loaded) {
                Status = load_cache_chunk(Vcb, c, NULL);

                if (!NT_SUCCESS(Status)) {
                    ERR("load_cache_chunk returned %08x\n", Status);
                    release_chunk_lock(c, Vcb);
                    return Status;
                }
            }

            c->used -= Vcb->superblock.node_size;

            space_list_add(c, address, Vcb->superblock.node_size, rollback);

            release_chunk_lock(c, Vcb);
        } else
            ERR("could not find chunk for address %I64x\n", address);
    }

    return STATUS_SUCCESS;
}
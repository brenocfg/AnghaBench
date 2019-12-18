#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {scalar_t__ level; size_t num_items; int /*<<< orphan*/  tree_id; } ;
typedef  TYPE_3__ tree_header ;
struct TYPE_14__ {scalar_t__ obj_type; scalar_t__ offset; int /*<<< orphan*/  obj_id; } ;
struct TYPE_16__ {int size; int offset; TYPE_2__ key; } ;
typedef  TYPE_4__ leaf_node ;
struct TYPE_13__ {int /*<<< orphan*/  node_size; } ;
struct TYPE_17__ {TYPE_1__ superblock; } ;
typedef  TYPE_5__ device_extension ;
typedef  size_t ULONG ;
struct TYPE_19__ {scalar_t__ type; scalar_t__ data; } ;
struct TYPE_18__ {scalar_t__ size; scalar_t__ address; } ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_6__ EXTENT_DATA2 ;
typedef  TYPE_7__ EXTENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ EXTENT_TYPE_REGULAR ; 
 TYPE_3__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_3__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NormalPagePriority ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ TYPE_EXTENT_DATA ; 
 int /*<<< orphan*/  log_file_checksum_error (TYPE_5__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ read_data (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_file_checksum_error_shared(device_extension* Vcb, uint64_t treeaddr, uint64_t addr, uint64_t devid, uint64_t extent) {
    tree_header* tree;
    NTSTATUS Status;
    leaf_node* ln;
    ULONG i;

    tree = ExAllocatePoolWithTag(PagedPool, Vcb->superblock.node_size, ALLOC_TAG);
    if (!tree) {
        ERR("out of memory\n");
        return;
    }

    Status = read_data(Vcb, treeaddr, Vcb->superblock.node_size, NULL, true, (uint8_t*)tree, NULL, NULL, NULL, 0, false, NormalPagePriority);
    if (!NT_SUCCESS(Status)) {
        ERR("read_data returned %08x\n", Status);
        goto end;
    }

    if (tree->level != 0) {
        ERR("tree level was %x, expected 0\n", tree->level);
        goto end;
    }

    ln = (leaf_node*)&tree[1];

    for (i = 0; i < tree->num_items; i++) {
        if (ln[i].key.obj_type == TYPE_EXTENT_DATA && ln[i].size >= sizeof(EXTENT_DATA) - 1 + sizeof(EXTENT_DATA2)) {
            EXTENT_DATA* ed = (EXTENT_DATA*)((uint8_t*)tree + sizeof(tree_header) + ln[i].offset);
            EXTENT_DATA2* ed2 = (EXTENT_DATA2*)ed->data;

            if (ed->type == EXTENT_TYPE_REGULAR && ed2->size != 0 && ed2->address == addr)
                log_file_checksum_error(Vcb, addr, devid, tree->tree_id, ln[i].key.obj_id, ln[i].key.offset + addr - extent);
        }
    }

end:
    ExFreePool(tree);
}
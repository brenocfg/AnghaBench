#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_28__ {TYPE_3__* item; } ;
typedef  TYPE_5__ traverse_ptr ;
struct TYPE_29__ {scalar_t__ size; scalar_t__ address; int /*<<< orphan*/  list_entry; } ;
typedef  TYPE_6__ space ;
struct TYPE_24__ {int compat_ro_flags; int generation; int cache_generation; scalar_t__ node_size; } ;
struct TYPE_30__ {TYPE_1__ superblock; int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_7__ device_extension ;
struct TYPE_31__ {scalar_t__ offset; int /*<<< orphan*/  space_size; int /*<<< orphan*/  space; TYPE_4__* chunk_item; } ;
typedef  TYPE_8__ chunk ;
struct TYPE_32__ {scalar_t__ obj_id; scalar_t__ offset; scalar_t__ obj_type; } ;
struct TYPE_27__ {scalar_t__ size; } ;
struct TYPE_25__ {scalar_t__ obj_id; scalar_t__ obj_type; scalar_t__ offset; } ;
struct TYPE_26__ {TYPE_2__ key; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_9__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int BTRFS_COMPAT_RO_FLAGS_FREE_SPACE_CACHE ; 
 int BTRFS_COMPAT_RO_FLAGS_FREE_SPACE_CACHE_VALID ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 TYPE_6__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_NOT_FOUND ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 scalar_t__ TYPE_METADATA_ITEM ; 
 scalar_t__ find_item (TYPE_7__*,int /*<<< orphan*/ ,TYPE_5__*,TYPE_9__*,int,int /*<<< orphan*/ ) ; 
 int find_next_item (TYPE_7__*,TYPE_5__*,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ load_stored_free_space_cache (TYPE_7__*,TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ load_stored_free_space_tree (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  order_space_entry (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS load_free_space_cache(device_extension* Vcb, chunk* c, PIRP Irp) {
    traverse_ptr tp, next_tp;
    KEY searchkey;
    uint64_t lastaddr;
    bool b;
    space* s;
    NTSTATUS Status;

    if (Vcb->superblock.compat_ro_flags & BTRFS_COMPAT_RO_FLAGS_FREE_SPACE_CACHE && Vcb->superblock.compat_ro_flags & BTRFS_COMPAT_RO_FLAGS_FREE_SPACE_CACHE_VALID) {
        Status = load_stored_free_space_tree(Vcb, c, Irp);

        if (!NT_SUCCESS(Status) && Status != STATUS_NOT_FOUND) {
            ERR("load_stored_free_space_tree returned %08x\n", Status);
            return Status;
        }
    } else if (Vcb->superblock.generation - 1 == Vcb->superblock.cache_generation) {
        Status = load_stored_free_space_cache(Vcb, c, false, Irp);

        if (!NT_SUCCESS(Status) && Status != STATUS_NOT_FOUND) {
            ERR("load_stored_free_space_cache returned %08x\n", Status);
            return Status;
        }
    } else
        Status = STATUS_NOT_FOUND;

    if (Status == STATUS_NOT_FOUND) {
        TRACE("generating free space cache for chunk %I64x\n", c->offset);

        searchkey.obj_id = c->offset;
        searchkey.obj_type = TYPE_EXTENT_ITEM;
        searchkey.offset = 0;

        Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, false, Irp);
        if (!NT_SUCCESS(Status)) {
            ERR("error - find_item returned %08x\n", Status);
            return Status;
        }

        lastaddr = c->offset;

        do {
            if (tp.item->key.obj_id >= c->offset + c->chunk_item->size)
                break;

            if (tp.item->key.obj_id >= c->offset && (tp.item->key.obj_type == TYPE_EXTENT_ITEM || tp.item->key.obj_type == TYPE_METADATA_ITEM)) {
                if (tp.item->key.obj_id > lastaddr) {
                    s = ExAllocatePoolWithTag(PagedPool, sizeof(space), ALLOC_TAG);

                    if (!s) {
                        ERR("out of memory\n");
                        return STATUS_INSUFFICIENT_RESOURCES;
                    }

                    s->address = lastaddr;
                    s->size = tp.item->key.obj_id - lastaddr;
                    InsertTailList(&c->space, &s->list_entry);

                    order_space_entry(s, &c->space_size);

                    TRACE("(%I64x,%I64x)\n", s->address, s->size);
                }

                if (tp.item->key.obj_type == TYPE_METADATA_ITEM)
                    lastaddr = tp.item->key.obj_id + Vcb->superblock.node_size;
                else
                    lastaddr = tp.item->key.obj_id + tp.item->key.offset;
            }

            b = find_next_item(Vcb, &tp, &next_tp, false, Irp);
            if (b)
                tp = next_tp;
        } while (b);

        if (lastaddr < c->offset + c->chunk_item->size) {
            s = ExAllocatePoolWithTag(PagedPool, sizeof(space), ALLOC_TAG);

            if (!s) {
                ERR("out of memory\n");
                return STATUS_INSUFFICIENT_RESOURCES;
            }

            s->address = lastaddr;
            s->size = c->offset + c->chunk_item->size - lastaddr;
            InsertTailList(&c->space, &s->list_entry);

            order_space_entry(s, &c->space_size);

            TRACE("(%I64x,%I64x)\n", s->address, s->size);
        }
    }

    return STATUS_SUCCESS;
}
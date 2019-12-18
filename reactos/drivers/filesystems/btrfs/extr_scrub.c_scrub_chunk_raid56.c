#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_23__ {TYPE_4__* item; } ;
typedef  TYPE_5__ traverse_ptr ;
struct TYPE_20__ {scalar_t__ node_size; scalar_t__ sector_size; } ;
struct TYPE_24__ {TYPE_2__ superblock; int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_6__ device_extension ;
struct TYPE_25__ {scalar_t__ offset; TYPE_1__* chunk_item; } ;
typedef  TYPE_7__ chunk ;
typedef  int ULONG ;
struct TYPE_26__ {int offset; scalar_t__ obj_type; scalar_t__ obj_id; } ;
struct TYPE_21__ {scalar_t__ obj_id; scalar_t__ obj_type; scalar_t__ offset; } ;
struct TYPE_22__ {TYPE_3__ key; } ;
struct TYPE_19__ {int type; int num_stripes; int stripe_length; scalar_t__ size; } ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_8__ KEY ;

/* Variables and functions */
 int BLOCK_FLAG_RAID6 ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ STATUS_INTERNAL_ERROR ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 scalar_t__ TYPE_METADATA_ITEM ; 
 scalar_t__ find_item (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,TYPE_8__*,int,int /*<<< orphan*/ *) ; 
 int find_next_item (TYPE_6__*,TYPE_5__*,TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ scrub_chunk_raid56_stripe_run (TYPE_6__*,TYPE_7__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static NTSTATUS scrub_chunk_raid56(device_extension* Vcb, chunk* c, uint64_t* offset, bool* changed) {
    NTSTATUS Status;
    KEY searchkey;
    traverse_ptr tp;
    bool b;
    uint64_t full_stripe_len, stripe, stripe_start, stripe_end, total_data = 0;
    ULONG num_extents = 0, num_parity_stripes = c->chunk_item->type & BLOCK_FLAG_RAID6 ? 2 : 1;

    full_stripe_len = (c->chunk_item->num_stripes - num_parity_stripes) * c->chunk_item->stripe_length;
    stripe = (*offset - c->offset) / full_stripe_len;

    *offset = c->offset + (stripe * full_stripe_len);

    searchkey.obj_id = *offset;
    searchkey.obj_type = TYPE_METADATA_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, false, NULL);
    if (!NT_SUCCESS(Status)) {
        ERR("find_item returned %08x\n", Status);
        return Status;
    }

    *changed = false;

    do {
        traverse_ptr next_tp;

        if (tp.item->key.obj_id >= c->offset + c->chunk_item->size)
            break;

        if (tp.item->key.obj_id >= *offset && (tp.item->key.obj_type == TYPE_EXTENT_ITEM || tp.item->key.obj_type == TYPE_METADATA_ITEM)) {
            uint64_t size = tp.item->key.obj_type == TYPE_METADATA_ITEM ? Vcb->superblock.node_size : tp.item->key.offset;

            TRACE("%I64x\n", tp.item->key.obj_id);

            if (size < Vcb->superblock.sector_size) {
                ERR("extent %I64x has size less than sector_size (%I64x < %x)\n", tp.item->key.obj_id, Vcb->superblock.sector_size);
                return STATUS_INTERNAL_ERROR;
            }

            stripe = (tp.item->key.obj_id - c->offset) / full_stripe_len;

            if (*changed) {
                if (stripe > stripe_end + 1) {
                    Status = scrub_chunk_raid56_stripe_run(Vcb, c, stripe_start, stripe_end);
                    if (!NT_SUCCESS(Status)) {
                        ERR("scrub_chunk_raid56_stripe_run returned %08x\n", Status);
                        return Status;
                    }

                    stripe_start = stripe;
                }
            } else
                stripe_start = stripe;

            stripe_end = (tp.item->key.obj_id + size - 1 - c->offset) / full_stripe_len;

            *changed = true;

            total_data += size;
            num_extents++;

            // only do so much at a time
            if (num_extents >= 64 || total_data >= 0x8000000) // 128 MB
                break;
        }

        b = find_next_item(Vcb, &tp, &next_tp, false, NULL);

        if (b)
            tp = next_tp;
    } while (b);

    if (*changed) {
        Status = scrub_chunk_raid56_stripe_run(Vcb, c, stripe_start, stripe_end);
        if (!NT_SUCCESS(Status)) {
            ERR("scrub_chunk_raid56_stripe_run returned %08x\n", Status);
            return Status;
        }

        *offset = c->offset + ((stripe_end + 1) * full_stripe_len);
    }

    return STATUS_SUCCESS;
}
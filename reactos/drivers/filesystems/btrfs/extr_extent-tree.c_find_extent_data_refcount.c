#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_13__ {TYPE_1__* item; } ;
typedef  TYPE_2__ traverse_ptr ;
struct TYPE_14__ {int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_3__ device_extension ;
typedef  scalar_t__ ULONG ;
struct TYPE_17__ {scalar_t__ obj_id; scalar_t__ obj_type; scalar_t__ offset; } ;
struct TYPE_16__ {scalar_t__ root; scalar_t__ objid; scalar_t__ offset; scalar_t__ count; } ;
struct TYPE_15__ {scalar_t__ obj_id; scalar_t__ obj_type; int offset; } ;
struct TYPE_12__ {int size; scalar_t__ data; TYPE_7__ key; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ KEY ;
typedef  int /*<<< orphan*/  EXTENT_ITEM ;
typedef  TYPE_5__ EXTENT_DATA_REF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 scalar_t__ TYPE_EXTENT_DATA_REF ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 int /*<<< orphan*/  find_item (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_extent_data_len (scalar_t__) ; 
 int get_extent_data_ref_hash2 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ get_extent_data_refcount (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  keycmp (TYPE_4__,TYPE_7__) ; 

__attribute__((used)) static uint32_t find_extent_data_refcount(device_extension* Vcb, uint64_t address, uint64_t size, uint64_t root, uint64_t objid, uint64_t offset, PIRP Irp) {
    NTSTATUS Status;
    KEY searchkey;
    traverse_ptr tp;

    searchkey.obj_id = address;
    searchkey.obj_type = TYPE_EXTENT_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, false, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);
        return 0;
    }

    if (tp.item->key.obj_id != searchkey.obj_id || tp.item->key.obj_type != searchkey.obj_type) {
        TRACE("could not find address %I64x in extent tree\n", address);
        return 0;
    }

    if (tp.item->key.offset != size) {
        ERR("extent %I64x had size %I64x, not %I64x as expected\n", address, tp.item->key.offset, size);
        return 0;
    }

    if (tp.item->size >= sizeof(EXTENT_ITEM)) {
        EXTENT_ITEM* ei = (EXTENT_ITEM*)tp.item->data;
        uint32_t len = tp.item->size - sizeof(EXTENT_ITEM);
        uint8_t* ptr = (uint8_t*)&ei[1];

        while (len > 0) {
            uint8_t secttype = *ptr;
            ULONG sectlen = get_extent_data_len(secttype);
            uint32_t sectcount = get_extent_data_refcount(secttype, ptr + sizeof(uint8_t));

            len--;

            if (sectlen > len) {
                ERR("(%I64x,%x,%I64x): %x bytes left, expecting at least %x\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, len, sectlen);
                return 0;
            }

            if (sectlen == 0) {
                ERR("(%I64x,%x,%I64x): unrecognized extent type %x\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, secttype);
                return 0;
            }

            if (secttype == TYPE_EXTENT_DATA_REF) {
                EXTENT_DATA_REF* sectedr = (EXTENT_DATA_REF*)(ptr + sizeof(uint8_t));

                if (sectedr->root == root && sectedr->objid == objid && sectedr->offset == offset)
                    return sectcount;
            }

            len -= sectlen;
            ptr += sizeof(uint8_t) + sectlen;
        }
    }

    searchkey.obj_id = address;
    searchkey.obj_type = TYPE_EXTENT_DATA_REF;
    searchkey.offset = get_extent_data_ref_hash2(root, objid, offset);

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, false, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("error - find_item returned %08x\n", Status);
        return 0;
    }

    if (!keycmp(searchkey, tp.item->key)) {
        if (tp.item->size < sizeof(EXTENT_DATA_REF))
            ERR("(%I64x,%x,%I64x) has size %u, not %u as expected\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, tp.item->size, sizeof(EXTENT_DATA_REF));
        else {
            EXTENT_DATA_REF* edr = (EXTENT_DATA_REF*)tp.item->data;

            return edr->count;
        }
    }

    return 0;
}
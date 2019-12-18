#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_30__ {TYPE_2__* item; } ;
typedef  TYPE_4__ traverse_ptr ;
struct TYPE_27__ {scalar_t__ sector_size; scalar_t__ node_size; } ;
struct TYPE_31__ {TYPE_1__ superblock; int /*<<< orphan*/  extent_root; } ;
typedef  TYPE_5__ device_extension ;
typedef  int ULONG ;
struct TYPE_35__ {scalar_t__ obj_type; int offset; scalar_t__ obj_id; } ;
struct TYPE_34__ {scalar_t__ offset; } ;
struct TYPE_33__ {scalar_t__ offset; scalar_t__ count; } ;
struct TYPE_32__ {scalar_t__ offset; } ;
struct TYPE_29__ {scalar_t__ obj_type; scalar_t__ obj_id; scalar_t__ offset; } ;
struct TYPE_28__ {int size; TYPE_3__ key; scalar_t__ data; } ;
struct TYPE_26__ {scalar_t__ offset; scalar_t__ count; int /*<<< orphan*/  objid; int /*<<< orphan*/  root; } ;
struct TYPE_25__ {int flags; scalar_t__ refcount; } ;
struct TYPE_24__ {scalar_t__ level; int /*<<< orphan*/  firstitem; } ;
typedef  TYPE_6__ TREE_BLOCK_REF ;
typedef  TYPE_7__ SHARED_DATA_REF ;
typedef  TYPE_8__ SHARED_BLOCK_REF ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_9__ KEY ;
typedef  TYPE_10__ EXTENT_ITEM2 ;
typedef  TYPE_11__ EXTENT_ITEM ;
typedef  TYPE_12__ EXTENT_DATA_REF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 int EXTENT_ITEM_TREE_BLOCK ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_EXTENT_DATA_REF ; 
 scalar_t__ TYPE_EXTENT_ITEM ; 
 scalar_t__ TYPE_METADATA_ITEM ; 
 scalar_t__ TYPE_SHARED_BLOCK_REF ; 
 scalar_t__ TYPE_SHARED_DATA_REF ; 
 scalar_t__ TYPE_TREE_BLOCK_REF ; 
 int /*<<< orphan*/  find_item (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_9__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ find_next_item (TYPE_5__*,TYPE_4__*,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_file_checksum_error (TYPE_5__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  log_file_checksum_error_shared (TYPE_5__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  log_tree_checksum_error (TYPE_5__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_tree_checksum_error_shared (TYPE_5__*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void log_unrecoverable_error(device_extension* Vcb, uint64_t address, uint64_t devid) {
    KEY searchkey;
    traverse_ptr tp;
    NTSTATUS Status;
    EXTENT_ITEM* ei;
    EXTENT_ITEM2* ei2 = NULL;
    uint8_t* ptr;
    ULONG len;
    uint64_t rc;

    // FIXME - still log even if rest of this function fails

    searchkey.obj_id = address;
    searchkey.obj_type = TYPE_METADATA_ITEM;
    searchkey.offset = 0xffffffffffffffff;

    Status = find_item(Vcb, Vcb->extent_root, &tp, &searchkey, false, NULL);
    if (!NT_SUCCESS(Status)) {
        ERR("find_item returned %08x\n", Status);
        return;
    }

    if ((tp.item->key.obj_type != TYPE_EXTENT_ITEM && tp.item->key.obj_type != TYPE_METADATA_ITEM) ||
        tp.item->key.obj_id >= address + Vcb->superblock.sector_size ||
        (tp.item->key.obj_type == TYPE_EXTENT_ITEM && tp.item->key.obj_id + tp.item->key.offset <= address) ||
        (tp.item->key.obj_type == TYPE_METADATA_ITEM && tp.item->key.obj_id + Vcb->superblock.node_size <= address)
    )
        return;

    if (tp.item->size < sizeof(EXTENT_ITEM)) {
        ERR("(%I64x,%x,%I64x) was %u bytes, expected at least %u\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset, tp.item->size, sizeof(EXTENT_ITEM));
        return;
    }

    ei = (EXTENT_ITEM*)tp.item->data;
    ptr = (uint8_t*)&ei[1];
    len = tp.item->size - sizeof(EXTENT_ITEM);

    if (tp.item->key.obj_id == TYPE_EXTENT_ITEM && ei->flags & EXTENT_ITEM_TREE_BLOCK) {
        if (tp.item->size < sizeof(EXTENT_ITEM) + sizeof(EXTENT_ITEM2)) {
            ERR("(%I64x,%x,%I64x) was %u bytes, expected at least %u\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset,
                                                                       tp.item->size, sizeof(EXTENT_ITEM) + sizeof(EXTENT_ITEM2));
            return;
        }

        ei2 = (EXTENT_ITEM2*)ptr;

        ptr += sizeof(EXTENT_ITEM2);
        len -= sizeof(EXTENT_ITEM2);
    }

    rc = 0;

    while (len > 0) {
        uint8_t type = *ptr;

        ptr++;
        len--;

        if (type == TYPE_TREE_BLOCK_REF) {
            TREE_BLOCK_REF* tbr;

            if (len < sizeof(TREE_BLOCK_REF)) {
                ERR("TREE_BLOCK_REF takes up %u bytes, but only %u remaining\n", sizeof(TREE_BLOCK_REF), len);
                break;
            }

            tbr = (TREE_BLOCK_REF*)ptr;

            log_tree_checksum_error(Vcb, address, devid, tbr->offset, ei2 ? ei2->level : (uint8_t)tp.item->key.offset, ei2 ? &ei2->firstitem : NULL);

            rc++;

            ptr += sizeof(TREE_BLOCK_REF);
            len -= sizeof(TREE_BLOCK_REF);
        } else if (type == TYPE_EXTENT_DATA_REF) {
            EXTENT_DATA_REF* edr;

            if (len < sizeof(EXTENT_DATA_REF)) {
                ERR("EXTENT_DATA_REF takes up %u bytes, but only %u remaining\n", sizeof(EXTENT_DATA_REF), len);
                break;
            }

            edr = (EXTENT_DATA_REF*)ptr;

            log_file_checksum_error(Vcb, address, devid, edr->root, edr->objid, edr->offset + address - tp.item->key.obj_id);

            rc += edr->count;

            ptr += sizeof(EXTENT_DATA_REF);
            len -= sizeof(EXTENT_DATA_REF);
        } else if (type == TYPE_SHARED_BLOCK_REF) {
            SHARED_BLOCK_REF* sbr;

            if (len < sizeof(SHARED_BLOCK_REF)) {
                ERR("SHARED_BLOCK_REF takes up %u bytes, but only %u remaining\n", sizeof(SHARED_BLOCK_REF), len);
                break;
            }

            sbr = (SHARED_BLOCK_REF*)ptr;

            log_tree_checksum_error_shared(Vcb, sbr->offset, address, devid);

            rc++;

            ptr += sizeof(SHARED_BLOCK_REF);
            len -= sizeof(SHARED_BLOCK_REF);
        } else if (type == TYPE_SHARED_DATA_REF) {
            SHARED_DATA_REF* sdr;

            if (len < sizeof(SHARED_DATA_REF)) {
                ERR("SHARED_DATA_REF takes up %u bytes, but only %u remaining\n", sizeof(SHARED_DATA_REF), len);
                break;
            }

            sdr = (SHARED_DATA_REF*)ptr;

            log_file_checksum_error_shared(Vcb, sdr->offset, address, devid, tp.item->key.obj_id);

            rc += sdr->count;

            ptr += sizeof(SHARED_DATA_REF);
            len -= sizeof(SHARED_DATA_REF);
        } else {
            ERR("unknown extent type %x\n", type);
            break;
        }
    }

    if (rc < ei->refcount) {
        do {
            traverse_ptr next_tp;

            if (find_next_item(Vcb, &tp, &next_tp, false, NULL))
                tp = next_tp;
            else
                break;

            if (tp.item->key.obj_id == address) {
                if (tp.item->key.obj_type == TYPE_TREE_BLOCK_REF)
                    log_tree_checksum_error(Vcb, address, devid, tp.item->key.offset, ei2 ? ei2->level : (uint8_t)tp.item->key.offset, ei2 ? &ei2->firstitem : NULL);
                else if (tp.item->key.obj_type == TYPE_EXTENT_DATA_REF) {
                    EXTENT_DATA_REF* edr;

                    if (tp.item->size < sizeof(EXTENT_DATA_REF)) {
                        ERR("(%I64x,%x,%I64x) was %u bytes, expected %u\n", tp.item->key.obj_id, tp.item->key.obj_type, tp.item->key.offset,
                                                                          tp.item->size, sizeof(EXTENT_DATA_REF));
                        break;
                    }

                    edr = (EXTENT_DATA_REF*)tp.item->data;

                    log_file_checksum_error(Vcb, address, devid, edr->root, edr->objid, edr->offset + address - tp.item->key.obj_id);
                } else if (tp.item->key.obj_type == TYPE_SHARED_BLOCK_REF)
                    log_tree_checksum_error_shared(Vcb, tp.item->key.offset, address, devid);
                else if (tp.item->key.obj_type == TYPE_SHARED_DATA_REF)
                    log_file_checksum_error_shared(Vcb, tp.item->key.offset, address, devid, tp.item->key.obj_id);
            } else
                break;
        } while (true);
    }
}
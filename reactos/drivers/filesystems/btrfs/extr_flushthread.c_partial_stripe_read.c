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
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ partial_stripe ;
struct TYPE_11__ {int sector_size; } ;
struct TYPE_15__ {TYPE_1__ superblock; } ;
typedef  TYPE_5__ device_extension ;
struct TYPE_16__ {TYPE_2__* chunk_item; TYPE_3__** devices; } ;
typedef  TYPE_6__ chunk ;
typedef  scalar_t__ ULONG ;
struct TYPE_17__ {scalar_t__ offset; } ;
struct TYPE_13__ {int /*<<< orphan*/  fileobj; scalar_t__ devobj; } ;
struct TYPE_12__ {int stripe_length; scalar_t__ num_stripes; int type; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_7__ CHUNK_ITEM_STRIPE ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int BLOCK_FLAG_RAID5 ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNEXPECTED_IO_ERROR ; 
 int /*<<< orphan*/  do_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  raid6_recover2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_read_phys (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NTSTATUS partial_stripe_read(device_extension* Vcb, chunk* c, partial_stripe* ps, uint64_t startoff, uint16_t parity, ULONG offset, ULONG len) {
    NTSTATUS Status;
    ULONG sl = (ULONG)(c->chunk_item->stripe_length / Vcb->superblock.sector_size);
    CHUNK_ITEM_STRIPE* cis = (CHUNK_ITEM_STRIPE*)&c->chunk_item[1];

    while (len > 0) {
        ULONG readlen = min(offset + len, offset + (sl - (offset % sl))) - offset;
        uint16_t stripe;

        stripe = (parity + (offset / sl) + 1) % c->chunk_item->num_stripes;

        if (c->devices[stripe]->devobj) {
            Status = sync_read_phys(c->devices[stripe]->devobj, c->devices[stripe]->fileobj, cis[stripe].offset + startoff + ((offset % sl) * Vcb->superblock.sector_size),
                                    readlen * Vcb->superblock.sector_size, ps->data + (offset * Vcb->superblock.sector_size), false);
            if (!NT_SUCCESS(Status)) {
                ERR("sync_read_phys returned %08x\n", Status);
                return Status;
            }
        } else if (c->chunk_item->type & BLOCK_FLAG_RAID5) {
            uint16_t i;
            uint8_t* scratch;

            scratch = ExAllocatePoolWithTag(NonPagedPool, readlen * Vcb->superblock.sector_size, ALLOC_TAG);
            if (!scratch) {
                ERR("out of memory\n");
                return STATUS_INSUFFICIENT_RESOURCES;
            }

            for (i = 0; i < c->chunk_item->num_stripes; i++) {
                if (i != stripe) {
                    if (!c->devices[i]->devobj) {
                        ExFreePool(scratch);
                        return STATUS_UNEXPECTED_IO_ERROR;
                    }

                    if (i == 0 || (stripe == 0 && i == 1)) {
                        Status = sync_read_phys(c->devices[i]->devobj, c->devices[i]->fileobj, cis[i].offset + startoff + ((offset % sl) * Vcb->superblock.sector_size),
                                                readlen * Vcb->superblock.sector_size, ps->data + (offset * Vcb->superblock.sector_size), false);
                        if (!NT_SUCCESS(Status)) {
                            ERR("sync_read_phys returned %08x\n", Status);
                            ExFreePool(scratch);
                            return Status;
                        }
                    } else {
                        Status = sync_read_phys(c->devices[i]->devobj, c->devices[i]->fileobj, cis[i].offset + startoff + ((offset % sl) * Vcb->superblock.sector_size),
                                                readlen * Vcb->superblock.sector_size, scratch, false);
                        if (!NT_SUCCESS(Status)) {
                            ERR("sync_read_phys returned %08x\n", Status);
                            ExFreePool(scratch);
                            return Status;
                        }

                        do_xor(ps->data + (offset * Vcb->superblock.sector_size), scratch, readlen * Vcb->superblock.sector_size);
                    }
                }
            }

            ExFreePool(scratch);
        } else {
            uint8_t* scratch;
            uint16_t k, i, logstripe, error_stripe, num_errors = 0;

            scratch = ExAllocatePoolWithTag(NonPagedPool, (c->chunk_item->num_stripes + 2) * readlen * Vcb->superblock.sector_size, ALLOC_TAG);
            if (!scratch) {
                ERR("out of memory\n");
                return STATUS_INSUFFICIENT_RESOURCES;
            }

            i = (parity + 1) % c->chunk_item->num_stripes;
            for (k = 0; k < c->chunk_item->num_stripes; k++) {
                if (i != stripe) {
                    if (c->devices[i]->devobj) {
                        Status = sync_read_phys(c->devices[i]->devobj, c->devices[i]->fileobj, cis[i].offset + startoff + ((offset % sl) * Vcb->superblock.sector_size),
                                                readlen * Vcb->superblock.sector_size, scratch + (k * readlen * Vcb->superblock.sector_size), false);
                        if (!NT_SUCCESS(Status)) {
                            ERR("sync_read_phys returned %08x\n", Status);
                            num_errors++;
                            error_stripe = k;
                        }
                    } else {
                        num_errors++;
                        error_stripe = k;
                    }

                    if (num_errors > 1) {
                        ExFreePool(scratch);
                        return STATUS_UNEXPECTED_IO_ERROR;
                    }
                } else
                    logstripe = k;

                i = (i + 1) % c->chunk_item->num_stripes;
            }

            if (num_errors == 0 || error_stripe == c->chunk_item->num_stripes - 1) {
                for (k = 0; k < c->chunk_item->num_stripes - 1; k++) {
                    if (k != logstripe) {
                        if (k == 0 || (k == 1 && logstripe == 0)) {
                            RtlCopyMemory(ps->data + (offset * Vcb->superblock.sector_size), scratch + (k * readlen * Vcb->superblock.sector_size),
                                          readlen * Vcb->superblock.sector_size);
                        } else {
                            do_xor(ps->data + (offset * Vcb->superblock.sector_size), scratch + (k * readlen * Vcb->superblock.sector_size),
                                   readlen * Vcb->superblock.sector_size);
                        }
                    }
                }
            } else {
                raid6_recover2(scratch, c->chunk_item->num_stripes, readlen * Vcb->superblock.sector_size, logstripe,
                               error_stripe, scratch + (c->chunk_item->num_stripes * readlen * Vcb->superblock.sector_size));

                RtlCopyMemory(ps->data + (offset * Vcb->superblock.sector_size), scratch + (c->chunk_item->num_stripes * readlen * Vcb->superblock.sector_size),
                              readlen * Vcb->superblock.sector_size);
            }

            ExFreePool(scratch);
        }

        offset += readlen;
        len -= readlen;
    }

    return STATUS_SUCCESS;
}
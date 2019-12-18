#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
struct TYPE_18__ {TYPE_1__* item; } ;
typedef  TYPE_3__ traverse_ptr ;
struct TYPE_19__ {int /*<<< orphan*/  dev_root; } ;
typedef  TYPE_4__ device_extension ;
struct TYPE_17__ {int /*<<< orphan*/  dev_id; } ;
struct TYPE_20__ {TYPE_2__ devitem; int /*<<< orphan*/  stats; } ;
typedef  TYPE_5__ device ;
struct TYPE_21__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  obj_type; scalar_t__ obj_id; } ;
struct TYPE_16__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_6__ KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TYPE_DEV_STATS ; 
 int /*<<< orphan*/  delete_tree_item (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  find_item (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_tree_item (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keycmp (int /*<<< orphan*/ ,TYPE_6__) ; 

__attribute__((used)) static NTSTATUS flush_changed_dev_stats(device_extension* Vcb, device* dev, PIRP Irp) {
    NTSTATUS Status;
    KEY searchkey;
    traverse_ptr tp;
    uint16_t statslen;
    uint64_t* stats;

    searchkey.obj_id = 0;
    searchkey.obj_type = TYPE_DEV_STATS;
    searchkey.offset = dev->devitem.dev_id;

    Status = find_item(Vcb, Vcb->dev_root, &tp, &searchkey, false, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("find_item returned %08x\n", Status);
        return Status;
    }

    if (!keycmp(tp.item->key, searchkey)) {
        Status = delete_tree_item(Vcb, &tp);
        if (!NT_SUCCESS(Status)) {
            ERR("delete_tree_item returned %08x\n", Status);
            return Status;
        }
    }

    statslen = sizeof(uint64_t) * 5;
    stats = ExAllocatePoolWithTag(PagedPool, statslen, ALLOC_TAG);
    if (!stats) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlCopyMemory(stats, dev->stats, statslen);

    Status = insert_tree_item(Vcb, Vcb->dev_root, 0, TYPE_DEV_STATS, dev->devitem.dev_id, stats, statslen, NULL, Irp);
    if (!NT_SUCCESS(Status)) {
        ERR("insert_tree_item returned %08x\n", Status);
        ExFreePool(stats);
        return Status;
    }

    return STATUS_SUCCESS;
}
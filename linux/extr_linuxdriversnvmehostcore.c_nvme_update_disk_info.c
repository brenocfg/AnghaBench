#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {int lba_shift; scalar_t__ ms; int /*<<< orphan*/  pi_type; TYPE_2__* ctrl; int /*<<< orphan*/  ext; } ;
struct nvme_id_ns {int nsattr; int /*<<< orphan*/  nsze; } ;
struct gendisk {int /*<<< orphan*/  queue; } ;
typedef  int sector_t ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int NVME_F_METADATA_SUPPORTED ; 
 int /*<<< orphan*/  blk_get_integrity (struct gendisk*) ; 
 int /*<<< orphan*/  blk_integrity_unregister (struct gendisk*) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_io_min (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (int /*<<< orphan*/ ,unsigned short) ; 
 int le64_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_config_discard (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_init_integrity (struct gendisk*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ns_has_pi (struct nvme_ns*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  set_disk_ro (struct gendisk*,int) ; 

__attribute__((used)) static void nvme_update_disk_info(struct gendisk *disk,
		struct nvme_ns *ns, struct nvme_id_ns *id)
{
	sector_t capacity = le64_to_cpup(&id->nsze) << (ns->lba_shift - 9);
	unsigned short bs = 1 << ns->lba_shift;

	blk_mq_freeze_queue(disk->queue);
	blk_integrity_unregister(disk);

	blk_queue_logical_block_size(disk->queue, bs);
	blk_queue_physical_block_size(disk->queue, bs);
	blk_queue_io_min(disk->queue, bs);

	if (ns->ms && !ns->ext &&
	    (ns->ctrl->ops->flags & NVME_F_METADATA_SUPPORTED))
		nvme_init_integrity(disk, ns->ms, ns->pi_type);
	if (ns->ms && !nvme_ns_has_pi(ns) && !blk_get_integrity(disk))
		capacity = 0;

	set_capacity(disk, capacity);
	nvme_config_discard(ns);

	if (id->nsattr & (1 << 0))
		set_disk_ro(disk, true);
	else
		set_disk_ro(disk, false);

	blk_mq_unfreeze_queue(disk->queue);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_disk {TYPE_1__* device; int /*<<< orphan*/  index; struct gendisk* disk; } ;
struct request_queue {int dummy; } ;
struct gendisk {int /*<<< orphan*/ * private_data; struct request_queue* queue; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sdev_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scsi_disk*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  sd_index_ida ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static void scsi_disk_release(struct device *dev)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct gendisk *disk = sdkp->disk;
	struct request_queue *q = disk->queue;

	ida_free(&sd_index_ida, sdkp->index);

	/*
	 * Wait until all requests that are in progress have completed.
	 * This is necessary to avoid that e.g. scsi_end_request() crashes
	 * due to clearing the disk->private_data pointer. Wait from inside
	 * scsi_disk_release() instead of from sd_release() to avoid that
	 * freezing and unfreezing the request queue affects user space I/O
	 * in case multiple processes open a /dev/sd... node concurrently.
	 */
	blk_mq_freeze_queue(q);
	blk_mq_unfreeze_queue(q);

	disk->private_data = NULL;
	put_disk(disk);
	put_device(&sdkp->device->sdev_gendev);

	kfree(sdkp);
}
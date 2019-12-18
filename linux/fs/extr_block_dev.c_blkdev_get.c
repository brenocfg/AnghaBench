#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gendisk {int flags; } ;
struct block_device {int bd_write_holder; int /*<<< orphan*/  bd_mutex; struct gendisk* bd_disk; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int FMODE_WRITE ; 
 int GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int PTR_ERR (struct block_device*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __blkdev_get (struct block_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_abort_claiming (struct block_device*,struct block_device*,void*) ; 
 int /*<<< orphan*/  bd_finish_claiming (struct block_device*,struct block_device*,void*) ; 
 struct block_device* bd_start_claiming (struct block_device*,void*) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  disk_block_events (struct gendisk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int blkdev_get(struct block_device *bdev, fmode_t mode, void *holder)
{
	struct block_device *whole = NULL;
	int res;

	WARN_ON_ONCE((mode & FMODE_EXCL) && !holder);

	if ((mode & FMODE_EXCL) && holder) {
		whole = bd_start_claiming(bdev, holder);
		if (IS_ERR(whole)) {
			bdput(bdev);
			return PTR_ERR(whole);
		}
	}

	res = __blkdev_get(bdev, mode, 0);

	if (whole) {
		struct gendisk *disk = whole->bd_disk;

		/* finish claiming */
		mutex_lock(&bdev->bd_mutex);
		if (!res)
			bd_finish_claiming(bdev, whole, holder);
		else
			bd_abort_claiming(bdev, whole, holder);
		/*
		 * Block event polling for write claims if requested.  Any
		 * write holder makes the write_holder state stick until
		 * all are released.  This is good enough and tracking
		 * individual writeable reference is too fragile given the
		 * way @mode is used in blkdev_get/put().
		 */
		if (!res && (mode & FMODE_WRITE) && !bdev->bd_write_holder &&
		    (disk->flags & GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE)) {
			bdev->bd_write_holder = true;
			disk_block_events(disk);
		}

		mutex_unlock(&bdev->bd_mutex);
		bdput(whole);
	}

	return res;
}
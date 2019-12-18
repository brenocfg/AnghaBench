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
struct block_device {scalar_t__ bd_holders; int bd_write_holder; int /*<<< orphan*/  bd_mutex; int /*<<< orphan*/  bd_disk; TYPE_1__* bd_contains; int /*<<< orphan*/ * bd_holder; } ;
typedef  int fmode_t ;
struct TYPE_2__ {scalar_t__ bd_holders; int /*<<< orphan*/ * bd_holder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_EVENT_MEDIA_CHANGE ; 
 int FMODE_EXCL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __blkdev_put (struct block_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdev_lock ; 
 int /*<<< orphan*/  disk_flush_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_unblock_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void blkdev_put(struct block_device *bdev, fmode_t mode)
{
	mutex_lock(&bdev->bd_mutex);

	if (mode & FMODE_EXCL) {
		bool bdev_free;

		/*
		 * Release a claim on the device.  The holder fields
		 * are protected with bdev_lock.  bd_mutex is to
		 * synchronize disk_holder unlinking.
		 */
		spin_lock(&bdev_lock);

		WARN_ON_ONCE(--bdev->bd_holders < 0);
		WARN_ON_ONCE(--bdev->bd_contains->bd_holders < 0);

		/* bd_contains might point to self, check in a separate step */
		if ((bdev_free = !bdev->bd_holders))
			bdev->bd_holder = NULL;
		if (!bdev->bd_contains->bd_holders)
			bdev->bd_contains->bd_holder = NULL;

		spin_unlock(&bdev_lock);

		/*
		 * If this was the last claim, remove holder link and
		 * unblock evpoll if it was a write holder.
		 */
		if (bdev_free && bdev->bd_write_holder) {
			disk_unblock_events(bdev->bd_disk);
			bdev->bd_write_holder = false;
		}
	}

	/*
	 * Trigger event checking and tell drivers to flush MEDIA_CHANGE
	 * event.  This is to ensure detection of media removal commanded
	 * from userland - e.g. eject(1).
	 */
	disk_flush_events(bdev->bd_disk, DISK_EVENT_MEDIA_CHANGE);

	mutex_unlock(&bdev->bd_mutex);

	__blkdev_put(bdev, mode, 0);
}
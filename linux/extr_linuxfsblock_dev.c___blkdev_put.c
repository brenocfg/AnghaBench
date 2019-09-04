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
struct gendisk {TYPE_1__* fops; } ;
struct block_device {int /*<<< orphan*/  bd_mutex; struct block_device* bd_contains; struct gendisk* bd_disk; int /*<<< orphan*/ * bd_part; int /*<<< orphan*/  bd_openers; int /*<<< orphan*/  bd_holders; int /*<<< orphan*/  bd_part_count; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct gendisk*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdev_write_inode (struct block_device*) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  disk_put_part (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_bdev (struct block_device*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk_and_module (struct gendisk*) ; 
 int /*<<< orphan*/  stub1 (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_blockdev (struct block_device*) ; 

__attribute__((used)) static void __blkdev_put(struct block_device *bdev, fmode_t mode, int for_part)
{
	struct gendisk *disk = bdev->bd_disk;
	struct block_device *victim = NULL;

	mutex_lock_nested(&bdev->bd_mutex, for_part);
	if (for_part)
		bdev->bd_part_count--;

	if (!--bdev->bd_openers) {
		WARN_ON_ONCE(bdev->bd_holders);
		sync_blockdev(bdev);
		kill_bdev(bdev);

		bdev_write_inode(bdev);
	}
	if (bdev->bd_contains == bdev) {
		if (disk->fops->release)
			disk->fops->release(disk, mode);
	}
	if (!bdev->bd_openers) {
		disk_put_part(bdev->bd_part);
		bdev->bd_part = NULL;
		bdev->bd_disk = NULL;
		if (bdev != bdev->bd_contains)
			victim = bdev->bd_contains;
		bdev->bd_contains = NULL;

		put_disk_and_module(disk);
	}
	mutex_unlock(&bdev->bd_mutex);
	bdput(bdev);
	if (victim)
		__blkdev_put(victim, mode, 1);
}
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
struct gendisk {int dummy; } ;
struct block_device {int /*<<< orphan*/  bd_inode; int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 struct gendisk* get_gendisk (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ inode_unhashed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk_and_module (struct gendisk*) ; 

__attribute__((used)) static struct gendisk *bdev_get_gendisk(struct block_device *bdev, int *partno)
{
	struct gendisk *disk = get_gendisk(bdev->bd_dev, partno);

	if (!disk)
		return NULL;
	/*
	 * Now that we hold gendisk reference we make sure bdev we looked up is
	 * not stale. If it is, it means device got removed and created before
	 * we looked up gendisk and we fail open in such case. Associating
	 * unhashed bdev with newly created gendisk could lead to two bdevs
	 * (and thus two independent caches) being associated with one device
	 * which is bad.
	 */
	if (inode_unhashed(bdev->bd_inode)) {
		put_disk_and_module(disk);
		return NULL;
	}
	return disk;
}
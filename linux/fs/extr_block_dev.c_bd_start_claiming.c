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
struct block_device {void* bd_claiming; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 struct block_device* ERR_PTR (int) ; 
 int bd_prepare_to_claim (struct block_device*,struct block_device*,void*) ; 
 struct gendisk* bdev_get_gendisk (struct block_device*,int*) ; 
 int /*<<< orphan*/  bdev_lock ; 
 struct block_device* bdget_disk (struct gendisk*,int /*<<< orphan*/ ) ; 
 struct block_device* bdgrab (struct block_device*) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  put_disk_and_module (struct gendisk*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct block_device *bd_start_claiming(struct block_device *bdev, void *holder)
{
	struct gendisk *disk;
	struct block_device *whole;
	int partno, err;

	might_sleep();

	/*
	 * @bdev might not have been initialized properly yet, look up
	 * and grab the outer block device the hard way.
	 */
	disk = bdev_get_gendisk(bdev, &partno);
	if (!disk)
		return ERR_PTR(-ENXIO);

	/*
	 * Normally, @bdev should equal what's returned from bdget_disk()
	 * if partno is 0; however, some drivers (floppy) use multiple
	 * bdev's for the same physical device and @bdev may be one of the
	 * aliases.  Keep @bdev if partno is 0.  This means claimer
	 * tracking is broken for those devices but it has always been that
	 * way.
	 */
	if (partno)
		whole = bdget_disk(disk, 0);
	else
		whole = bdgrab(bdev);

	put_disk_and_module(disk);
	if (!whole)
		return ERR_PTR(-ENOMEM);

	/* prepare to claim, if successful, mark claiming in progress */
	spin_lock(&bdev_lock);

	err = bd_prepare_to_claim(bdev, whole, holder);
	if (err == 0) {
		whole->bd_claiming = holder;
		spin_unlock(&bdev_lock);
		return whole;
	} else {
		spin_unlock(&bdev_lock);
		bdput(whole);
		return ERR_PTR(err);
	}
}
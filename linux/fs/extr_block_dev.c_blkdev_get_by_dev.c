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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct block_device* ERR_PTR (int) ; 
 struct block_device* bdget (int /*<<< orphan*/ ) ; 
 int blkdev_get (struct block_device*,int /*<<< orphan*/ ,void*) ; 

struct block_device *blkdev_get_by_dev(dev_t dev, fmode_t mode, void *holder)
{
	struct block_device *bdev;
	int err;

	bdev = bdget(dev);
	if (!bdev)
		return ERR_PTR(-ENOMEM);

	err = blkdev_get(bdev, mode, holder);
	if (err)
		return ERR_PTR(err);

	return bdev;
}
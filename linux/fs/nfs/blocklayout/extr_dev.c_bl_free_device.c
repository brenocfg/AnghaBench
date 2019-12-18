#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pr_ops {int (* pr_register ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct pnfs_block_dev {int nr_children; TYPE_3__* bdev; int /*<<< orphan*/  pr_key; scalar_t__ pr_registered; struct pnfs_block_dev* children; } ;
struct TYPE_7__ {TYPE_2__* bd_disk; } ;
struct TYPE_6__ {TYPE_1__* fops; } ;
struct TYPE_5__ {struct pr_ops* pr_ops; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  blkdev_put (TYPE_3__*,int) ; 
 int /*<<< orphan*/  kfree (struct pnfs_block_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bl_free_device(struct pnfs_block_dev *dev)
{
	if (dev->nr_children) {
		int i;

		for (i = 0; i < dev->nr_children; i++)
			bl_free_device(&dev->children[i]);
		kfree(dev->children);
	} else {
		if (dev->pr_registered) {
			const struct pr_ops *ops =
				dev->bdev->bd_disk->fops->pr_ops;
			int error;

			error = ops->pr_register(dev->bdev, dev->pr_key, 0,
				false);
			if (error)
				pr_err("failed to unregister PR key.\n");
		}

		if (dev->bdev)
			blkdev_put(dev->bdev, FMODE_READ | FMODE_WRITE);
	}
}
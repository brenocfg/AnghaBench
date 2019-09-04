#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvmet_ns {TYPE_1__* bdev; int /*<<< orphan*/  blksize_shift; int /*<<< orphan*/  size; int /*<<< orphan*/  device_path; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int ENOTBLK ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  bdev_logical_block_size (TYPE_1__*) ; 
 TYPE_1__* blkdev_get_by_path (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blksize_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int nvmet_bdev_ns_enable(struct nvmet_ns *ns)
{
	int ret;

	ns->bdev = blkdev_get_by_path(ns->device_path,
			FMODE_READ | FMODE_WRITE, NULL);
	if (IS_ERR(ns->bdev)) {
		ret = PTR_ERR(ns->bdev);
		if (ret != -ENOTBLK) {
			pr_err("failed to open block device %s: (%ld)\n",
					ns->device_path, PTR_ERR(ns->bdev));
		}
		ns->bdev = NULL;
		return ret;
	}
	ns->size = i_size_read(ns->bdev->bd_inode);
	ns->blksize_shift = blksize_bits(bdev_logical_block_size(ns->bdev));
	return 0;
}
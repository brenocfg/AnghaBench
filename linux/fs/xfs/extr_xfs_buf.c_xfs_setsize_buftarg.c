#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int bt_meta_sectorsize; unsigned int bt_meta_sectormask; int /*<<< orphan*/  bt_bdev; void* bt_logical_sectormask; void* bt_logical_sectorsize; int /*<<< orphan*/  bt_mount; } ;
typedef  TYPE_1__ xfs_buftarg_t ;

/* Variables and functions */
 int EINVAL ; 
 void* bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 scalar_t__ set_blocksize (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xfs_warn (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 

int
xfs_setsize_buftarg(
	xfs_buftarg_t		*btp,
	unsigned int		sectorsize)
{
	/* Set up metadata sector size info */
	btp->bt_meta_sectorsize = sectorsize;
	btp->bt_meta_sectormask = sectorsize - 1;

	if (set_blocksize(btp->bt_bdev, sectorsize)) {
		xfs_warn(btp->bt_mount,
			"Cannot set_blocksize to %u on device %pg",
			sectorsize, btp->bt_bdev);
		return -EINVAL;
	}

	/* Set up device logical sector size mask */
	btp->bt_logical_sectorsize = bdev_logical_block_size(btp->bt_bdev);
	btp->bt_logical_sectormask = bdev_logical_block_size(btp->bt_bdev) - 1;

	return 0;
}
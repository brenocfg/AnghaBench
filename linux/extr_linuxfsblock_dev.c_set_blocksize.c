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
struct block_device {int bd_block_size; TYPE_1__* bd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_blkbits; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int bdev_logical_block_size (struct block_device*) ; 
 int /*<<< orphan*/  blksize_bits (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  kill_bdev (struct block_device*) ; 
 int /*<<< orphan*/  sync_blockdev (struct block_device*) ; 

int set_blocksize(struct block_device *bdev, int size)
{
	/* Size must be a power of two, and between 512 and PAGE_SIZE */
	if (size > PAGE_SIZE || size < 512 || !is_power_of_2(size))
		return -EINVAL;

	/* Size cannot be smaller than the size supported by the device */
	if (size < bdev_logical_block_size(bdev))
		return -EINVAL;

	/* Don't change the size if it is same as current */
	if (bdev->bd_block_size != size) {
		sync_blockdev(bdev);
		bdev->bd_block_size = size;
		bdev->bd_inode->i_blkbits = blksize_bits(size);
		kill_bdev(bdev);
	}
	return 0;
}
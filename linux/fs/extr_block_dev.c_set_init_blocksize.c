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
struct block_device {unsigned int bd_block_size; TYPE_1__* bd_inode; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_blkbits; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 unsigned int bdev_logical_block_size (struct block_device*) ; 
 int /*<<< orphan*/  blksize_bits (unsigned int) ; 
 unsigned int i_size_read (TYPE_1__*) ; 

__attribute__((used)) static void set_init_blocksize(struct block_device *bdev)
{
	unsigned bsize = bdev_logical_block_size(bdev);
	loff_t size = i_size_read(bdev->bd_inode);

	while (bsize < PAGE_SIZE) {
		if (size & bsize)
			break;
		bsize <<= 1;
	}
	bdev->bd_block_size = bsize;
	bdev->bd_inode->i_blkbits = blksize_bits(bsize);
}
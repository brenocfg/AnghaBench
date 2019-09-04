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
struct block_device {int /*<<< orphan*/  bd_inode; } ;
typedef  int sector_t ;
typedef  int loff_t ;

/* Variables and functions */
 unsigned int blksize_bits (unsigned int) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t blkdev_max_block(struct block_device *bdev, unsigned int size)
{
	sector_t retval = ~((sector_t)0);
	loff_t sz = i_size_read(bdev->bd_inode);

	if (sz) {
		unsigned int sizebits = blksize_bits(size);
		retval = (sz >> sizebits);
	}
	return retval;
}
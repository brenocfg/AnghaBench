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
typedef  unsigned int u64 ;
typedef  unsigned int sector_t ;
typedef  unsigned int pgoff_t ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ unlikely (int) ; 

int generic_check_addressable(unsigned blocksize_bits, u64 num_blocks)
{
	u64 last_fs_block = num_blocks - 1;
	u64 last_fs_page =
		last_fs_block >> (PAGE_SHIFT - blocksize_bits);

	if (unlikely(num_blocks == 0))
		return 0;

	if ((blocksize_bits < 9) || (blocksize_bits > PAGE_SHIFT))
		return -EINVAL;

	if ((last_fs_block > (sector_t)(~0ULL) >> (blocksize_bits - 9)) ||
	    (last_fs_page > (pgoff_t)(~0ULL))) {
		return -EFBIG;
	}
	return 0;
}
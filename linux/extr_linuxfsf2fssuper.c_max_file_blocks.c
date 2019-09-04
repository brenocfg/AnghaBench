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
typedef  int loff_t ;

/* Variables and functions */
 int ADDRS_PER_BLOCK ; 
 int NIDS_PER_BLOCK ; 

__attribute__((used)) static loff_t max_file_blocks(void)
{
	loff_t result = 0;
	loff_t leaf_count = ADDRS_PER_BLOCK;

	/*
	 * note: previously, result is equal to (DEF_ADDRS_PER_INODE -
	 * DEFAULT_INLINE_XATTR_ADDRS), but now f2fs try to reserve more
	 * space in inode.i_addr, it will be more safe to reassign
	 * result as zero.
	 */

	/* two direct node blocks */
	result += (leaf_count * 2);

	/* two indirect node blocks */
	leaf_count *= NIDS_PER_BLOCK;
	result += (leaf_count * 2);

	/* one double indirect node block */
	leaf_count *= NIDS_PER_BLOCK;
	result += leaf_count;

	return result;
}
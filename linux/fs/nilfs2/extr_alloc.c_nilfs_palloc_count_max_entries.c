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
typedef  unsigned long u64 ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int nilfs_palloc_count_desc_blocks (struct inode*,unsigned long*) ; 
 scalar_t__ nilfs_palloc_entries_per_group (struct inode*) ; 
 unsigned long nilfs_palloc_groups_per_desc_block (struct inode*) ; 
 scalar_t__ nilfs_palloc_mdt_file_can_grow (struct inode*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_palloc_count_max_entries(struct inode *inode, u64 nused, u64 *nmaxp)
{
	unsigned long desc_blocks = 0;
	u64 entries_per_desc_block, nmax;
	int err;

	err = nilfs_palloc_count_desc_blocks(inode, &desc_blocks);
	if (unlikely(err))
		return err;

	entries_per_desc_block = (u64)nilfs_palloc_entries_per_group(inode) *
				nilfs_palloc_groups_per_desc_block(inode);
	nmax = entries_per_desc_block * desc_blocks;

	if (nused == nmax &&
			nilfs_palloc_mdt_file_can_grow(inode, desc_blocks))
		nmax += entries_per_desc_block;

	if (nused > nmax)
		return -ERANGE;

	*nmaxp = nmax;
	return 0;
}
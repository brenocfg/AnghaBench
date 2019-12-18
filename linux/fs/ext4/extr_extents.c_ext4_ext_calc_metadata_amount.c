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
struct inode {TYPE_1__* i_sb; } ;
struct ext4_inode_info {int i_da_metadata_calc_len; scalar_t__ i_da_metadata_calc_last_lblock; } ;
struct ext4_extent_idx {int dummy; } ;
struct ext4_extent_header {int dummy; } ;
typedef  scalar_t__ ext4_lblk_t ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int ext_depth (struct inode*) ; 

int ext4_ext_calc_metadata_amount(struct inode *inode, ext4_lblk_t lblock)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	int idxs;

	idxs = ((inode->i_sb->s_blocksize - sizeof(struct ext4_extent_header))
		/ sizeof(struct ext4_extent_idx));

	/*
	 * If the new delayed allocation block is contiguous with the
	 * previous da block, it can share index blocks with the
	 * previous block, so we only need to allocate a new index
	 * block every idxs leaf blocks.  At ldxs**2 blocks, we need
	 * an additional index block, and at ldxs**3 blocks, yet
	 * another index blocks.
	 */
	if (ei->i_da_metadata_calc_len &&
	    ei->i_da_metadata_calc_last_lblock+1 == lblock) {
		int num = 0;

		if ((ei->i_da_metadata_calc_len % idxs) == 0)
			num++;
		if ((ei->i_da_metadata_calc_len % (idxs*idxs)) == 0)
			num++;
		if ((ei->i_da_metadata_calc_len % (idxs*idxs*idxs)) == 0) {
			num++;
			ei->i_da_metadata_calc_len = 0;
		} else
			ei->i_da_metadata_calc_len++;
		ei->i_da_metadata_calc_last_lblock++;
		return num;
	}

	/*
	 * In the worst case we need a new set of index blocks at
	 * every level of the inode's extent tree.
	 */
	ei->i_da_metadata_calc_len = 1;
	ei->i_da_metadata_calc_last_lblock = lblock;
	return ext_depth(inode) + 1;
}
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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_inode_info {int i_da_metadata_calc_len; int i_da_metadata_calc_last_lblock; } ;
typedef  int sector_t ;

/* Variables and functions */
 scalar_t__ EXT4_ADDR_PER_BLOCK (int /*<<< orphan*/ ) ; 
 int EXT4_ADDR_PER_BLOCK_BITS (int /*<<< orphan*/ ) ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int EXT4_NDIR_BLOCKS ; 
 int order_base_2 (int) ; 

int ext4_ind_calc_metadata_amount(struct inode *inode, sector_t lblock)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	sector_t dind_mask = ~((sector_t)EXT4_ADDR_PER_BLOCK(inode->i_sb) - 1);
	int blk_bits;

	if (lblock < EXT4_NDIR_BLOCKS)
		return 0;

	lblock -= EXT4_NDIR_BLOCKS;

	if (ei->i_da_metadata_calc_len &&
	    (lblock & dind_mask) == ei->i_da_metadata_calc_last_lblock) {
		ei->i_da_metadata_calc_len++;
		return 0;
	}
	ei->i_da_metadata_calc_last_lblock = lblock & dind_mask;
	ei->i_da_metadata_calc_len = 1;
	blk_bits = order_base_2(lblock);
	return (blk_bits / EXT4_ADDR_PER_BLOCK_BITS(inode->i_sb)) + 1;
}
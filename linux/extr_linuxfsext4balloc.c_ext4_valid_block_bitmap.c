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
struct super_block {int dummy; } ;
struct ext4_sb_info {scalar_t__ s_itb_per_group; } ;
struct ext4_group_desc {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  scalar_t__ ext4_grpblk_t ;
typedef  int /*<<< orphan*/  ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 scalar_t__ EXT4_B2C (struct ext4_sb_info*,scalar_t__) ; 
 scalar_t__ EXT4_CLUSTERS_PER_GROUP (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_find_next_zero_bit (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ext4_group_first_block_no (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_has_feature_flex_bg (struct super_block*) ; 
 scalar_t__ ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext4_fsblk_t ext4_valid_block_bitmap(struct super_block *sb,
					    struct ext4_group_desc *desc,
					    ext4_group_t block_group,
					    struct buffer_head *bh)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_grpblk_t offset;
	ext4_grpblk_t next_zero_bit;
	ext4_grpblk_t max_bit = EXT4_CLUSTERS_PER_GROUP(sb);
	ext4_fsblk_t blk;
	ext4_fsblk_t group_first_block;

	if (ext4_has_feature_flex_bg(sb)) {
		/* with FLEX_BG, the inode/block bitmaps and itable
		 * blocks may not be in the group at all
		 * so the bitmap validation will be skipped for those groups
		 * or it has to also read the block group where the bitmaps
		 * are located to verify they are set.
		 */
		return 0;
	}
	group_first_block = ext4_group_first_block_no(sb, block_group);

	/* check whether block bitmap block number is set */
	blk = ext4_block_bitmap(sb, desc);
	offset = blk - group_first_block;
	if (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    !ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
		/* bad block bitmap */
		return blk;

	/* check whether the inode bitmap block number is set */
	blk = ext4_inode_bitmap(sb, desc);
	offset = blk - group_first_block;
	if (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    !ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
		/* bad block bitmap */
		return blk;

	/* check whether the inode table block number is set */
	blk = ext4_inode_table(sb, desc);
	offset = blk - group_first_block;
	if (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    EXT4_B2C(sbi, offset + sbi->s_itb_per_group) >= max_bit)
		return blk;
	next_zero_bit = ext4_find_next_zero_bit(bh->b_data,
			EXT4_B2C(sbi, offset + sbi->s_itb_per_group),
			EXT4_B2C(sbi, offset));
	if (next_zero_bit <
	    EXT4_B2C(sbi, offset + sbi->s_itb_per_group))
		/* bad bitmap for inode tables */
		return blk;
	return 0;
}
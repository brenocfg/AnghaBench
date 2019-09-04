#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct ext4_inode_info {int i_block_group; } ;
typedef  int ext4_grpblk_t ;
typedef  int ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_5__ {int pid; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELALLOC ; 
 int EXT4_BLOCKS_PER_GROUP (int /*<<< orphan*/ ) ; 
 int EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 scalar_t__ ext4_blocks_count (int /*<<< orphan*/ ) ; 
 int ext4_flex_bg_size (TYPE_1__*) ; 
 scalar_t__ ext4_group_first_block_no (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ext4_fsblk_t ext4_inode_to_goal_block(struct inode *inode)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	ext4_group_t block_group;
	ext4_grpblk_t colour;
	int flex_size = ext4_flex_bg_size(EXT4_SB(inode->i_sb));
	ext4_fsblk_t bg_start;
	ext4_fsblk_t last_block;

	block_group = ei->i_block_group;
	if (flex_size >= EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME) {
		/*
		 * If there are at least EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME
		 * block groups per flexgroup, reserve the first block
		 * group for directories and special files.  Regular
		 * files will start at the second block group.  This
		 * tends to speed up directory access and improves
		 * fsck times.
		 */
		block_group &= ~(flex_size-1);
		if (S_ISREG(inode->i_mode))
			block_group++;
	}
	bg_start = ext4_group_first_block_no(inode->i_sb, block_group);
	last_block = ext4_blocks_count(EXT4_SB(inode->i_sb)->s_es) - 1;

	/*
	 * If we are doing delayed allocation, we don't need take
	 * colour into account.
	 */
	if (test_opt(inode->i_sb, DELALLOC))
		return bg_start;

	if (bg_start + EXT4_BLOCKS_PER_GROUP(inode->i_sb) <= last_block)
		colour = (current->pid % 16) *
			(EXT4_BLOCKS_PER_GROUP(inode->i_sb) / 16);
	else
		colour = (current->pid % 16) * ((last_block - bg_start) / 16);
	return bg_start + colour;
}
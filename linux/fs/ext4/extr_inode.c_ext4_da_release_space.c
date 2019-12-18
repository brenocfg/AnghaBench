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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_dirtyclusters_counter; } ;
struct ext4_inode_info {int i_reserved_data_blocks; int /*<<< orphan*/  i_block_reservation_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_C2B (struct ext4_sb_info*,int) ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dquot_release_reservation_block (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  percpu_counter_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ext4_da_release_space (struct inode*,int) ; 
 scalar_t__ unlikely (int) ; 

void ext4_da_release_space(struct inode *inode, int to_free)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct ext4_inode_info *ei = EXT4_I(inode);

	if (!to_free)
		return;		/* Nothing to release, exit */

	spin_lock(&EXT4_I(inode)->i_block_reservation_lock);

	trace_ext4_da_release_space(inode, to_free);
	if (unlikely(to_free > ei->i_reserved_data_blocks)) {
		/*
		 * if there aren't enough reserved blocks, then the
		 * counter is messed up somewhere.  Since this
		 * function is called from invalidate page, it's
		 * harmless to return without any action.
		 */
		ext4_warning(inode->i_sb, "ext4_da_release_space: "
			 "ino %lu, to_free %d with only %d reserved "
			 "data blocks", inode->i_ino, to_free,
			 ei->i_reserved_data_blocks);
		WARN_ON(1);
		to_free = ei->i_reserved_data_blocks;
	}
	ei->i_reserved_data_blocks -= to_free;

	/* update fs dirty data blocks counter */
	percpu_counter_sub(&sbi->s_dirtyclusters_counter, to_free);

	spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);

	dquot_release_reservation_block(inode, EXT4_C2B(sbi, to_free));
}
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
struct ext4_sb_info {int /*<<< orphan*/  s_freeclusters_counter; int /*<<< orphan*/  s_dirtyclusters_counter; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_block_reservation_lock; int /*<<< orphan*/  i_reserved_data_blocks; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_C2B (struct ext4_sb_info*,int) ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_reclaim_block (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_remove_pending (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_rereserve_cluster(struct inode *inode, ext4_lblk_t lblk)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct ext4_inode_info *ei = EXT4_I(inode);

	dquot_reclaim_block(inode, EXT4_C2B(sbi, 1));

	spin_lock(&ei->i_block_reservation_lock);
	ei->i_reserved_data_blocks++;
	percpu_counter_add(&sbi->s_dirtyclusters_counter, 1);
	spin_unlock(&ei->i_block_reservation_lock);

	percpu_counter_add(&sbi->s_freeclusters_counter, 1);
	ext4_remove_pending(inode, lblk);
}
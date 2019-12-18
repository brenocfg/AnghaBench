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
struct ext4_sb_info {int dummy; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_block_reservation_lock; int /*<<< orphan*/  i_reserved_data_blocks; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_C2B (struct ext4_sb_info*,int) ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_release_reservation_block (struct inode*,int /*<<< orphan*/ ) ; 
 int dquot_reserve_block (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_claim_free_clusters (struct ext4_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ext4_da_reserve_space (struct inode*) ; 

__attribute__((used)) static int ext4_da_reserve_space(struct inode *inode)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct ext4_inode_info *ei = EXT4_I(inode);
	int ret;

	/*
	 * We will charge metadata quota at writeout time; this saves
	 * us from metadata over-estimation, though we may go over by
	 * a small amount in the end.  Here we just reserve for data.
	 */
	ret = dquot_reserve_block(inode, EXT4_C2B(sbi, 1));
	if (ret)
		return ret;

	spin_lock(&ei->i_block_reservation_lock);
	if (ext4_claim_free_clusters(sbi, 1, 0)) {
		spin_unlock(&ei->i_block_reservation_lock);
		dquot_release_reservation_block(inode, EXT4_C2B(sbi, 1));
		return -ENOSPC;
	}
	ei->i_reserved_data_blocks++;
	trace_ext4_da_reserve_space(inode);
	spin_unlock(&ei->i_block_reservation_lock);

	return 0;       /* success */
}
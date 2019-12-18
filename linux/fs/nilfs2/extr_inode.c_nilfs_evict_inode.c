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
struct super_block {int dummy; } ;
struct nilfs_transaction_info {int dummy; } ;
struct nilfs_inode_info {TYPE_1__* i_root; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_data; scalar_t__ i_nlink; struct super_block* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  inodes_count; int /*<<< orphan*/  ifile; } ;

/* Variables and functions */
 scalar_t__ IS_SYNC (struct inode*) ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_TI_SYNC ; 
 int /*<<< orphan*/  atomic64_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  nilfs_clear_inode (struct inode*) ; 
 int nilfs_ifile_delete_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  nilfs_set_transaction_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_commit (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_truncate_bmap (struct nilfs_inode_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void nilfs_evict_inode(struct inode *inode)
{
	struct nilfs_transaction_info ti;
	struct super_block *sb = inode->i_sb;
	struct nilfs_inode_info *ii = NILFS_I(inode);
	int ret;

	if (inode->i_nlink || !ii->i_root || unlikely(is_bad_inode(inode))) {
		truncate_inode_pages_final(&inode->i_data);
		clear_inode(inode);
		nilfs_clear_inode(inode);
		return;
	}
	nilfs_transaction_begin(sb, &ti, 0); /* never fails */

	truncate_inode_pages_final(&inode->i_data);

	/* TODO: some of the following operations may fail.  */
	nilfs_truncate_bmap(ii, 0);
	nilfs_mark_inode_dirty(inode);
	clear_inode(inode);

	ret = nilfs_ifile_delete_inode(ii->i_root->ifile, inode->i_ino);
	if (!ret)
		atomic64_dec(&ii->i_root->inodes_count);

	nilfs_clear_inode(inode);

	if (IS_SYNC(inode))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);
	nilfs_transaction_commit(sb);
	/*
	 * May construct a logical segment and may fail in sync mode.
	 * But delete_inode has no return value.
	 */
}
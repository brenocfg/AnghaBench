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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_root {int /*<<< orphan*/  root_item; struct btrfs_fs_info* fs_info; } ;
struct btrfs_log_ctx {scalar_t__ log_new_dentries; } ;
struct TYPE_2__ {scalar_t__ i_nlink; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct btrfs_inode {scalar_t__ generation; scalar_t__ last_unlink_trans; TYPE_1__ vfs_inode; struct btrfs_root* root; } ;
struct btrfs_fs_info {scalar_t__ last_trans_committed; scalar_t__ last_trans_log_full_commit; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int BTRFS_NO_LOG_SYNC ; 
 int /*<<< orphan*/  NOTREELOG ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_log_trans (struct btrfs_root*) ; 
 scalar_t__ btrfs_inode_in_log (struct btrfs_inode*,int /*<<< orphan*/ ) ; 
 int btrfs_log_all_parents (struct btrfs_trans_handle*,struct btrfs_inode*,struct btrfs_log_ctx*) ; 
 int btrfs_log_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_inode*,int,int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct btrfs_log_ctx*) ; 
 int /*<<< orphan*/  btrfs_remove_log_ctx (struct btrfs_root*,struct btrfs_log_ctx*) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_set_log_full_commit (struct btrfs_trans_handle*) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int check_parent_dirs_for_sync (struct btrfs_trans_handle*,struct btrfs_inode*,struct dentry*,struct super_block*,scalar_t__) ; 
 int log_all_new_ancestors (struct btrfs_trans_handle*,struct btrfs_inode*,struct dentry*,struct btrfs_log_ctx*) ; 
 int log_new_dir_dentries (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_inode*,struct btrfs_log_ctx*) ; 
 int start_log_trans (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_log_ctx*) ; 

__attribute__((used)) static int btrfs_log_inode_parent(struct btrfs_trans_handle *trans,
				  struct btrfs_inode *inode,
				  struct dentry *parent,
				  const loff_t start,
				  const loff_t end,
				  int inode_only,
				  struct btrfs_log_ctx *ctx)
{
	struct btrfs_root *root = inode->root;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct super_block *sb;
	int ret = 0;
	u64 last_committed = fs_info->last_trans_committed;
	bool log_dentries = false;

	sb = inode->vfs_inode.i_sb;

	if (btrfs_test_opt(fs_info, NOTREELOG)) {
		ret = 1;
		goto end_no_trans;
	}

	/*
	 * The prev transaction commit doesn't complete, we need do
	 * full commit by ourselves.
	 */
	if (fs_info->last_trans_log_full_commit >
	    fs_info->last_trans_committed) {
		ret = 1;
		goto end_no_trans;
	}

	if (btrfs_root_refs(&root->root_item) == 0) {
		ret = 1;
		goto end_no_trans;
	}

	ret = check_parent_dirs_for_sync(trans, inode, parent, sb,
			last_committed);
	if (ret)
		goto end_no_trans;

	/*
	 * Skip already logged inodes or inodes corresponding to tmpfiles
	 * (since logging them is pointless, a link count of 0 means they
	 * will never be accessible).
	 */
	if (btrfs_inode_in_log(inode, trans->transid) ||
	    inode->vfs_inode.i_nlink == 0) {
		ret = BTRFS_NO_LOG_SYNC;
		goto end_no_trans;
	}

	ret = start_log_trans(trans, root, ctx);
	if (ret)
		goto end_no_trans;

	ret = btrfs_log_inode(trans, root, inode, inode_only, start, end, ctx);
	if (ret)
		goto end_trans;

	/*
	 * for regular files, if its inode is already on disk, we don't
	 * have to worry about the parents at all.  This is because
	 * we can use the last_unlink_trans field to record renames
	 * and other fun in this file.
	 */
	if (S_ISREG(inode->vfs_inode.i_mode) &&
	    inode->generation <= last_committed &&
	    inode->last_unlink_trans <= last_committed) {
		ret = 0;
		goto end_trans;
	}

	if (S_ISDIR(inode->vfs_inode.i_mode) && ctx && ctx->log_new_dentries)
		log_dentries = true;

	/*
	 * On unlink we must make sure all our current and old parent directory
	 * inodes are fully logged. This is to prevent leaving dangling
	 * directory index entries in directories that were our parents but are
	 * not anymore. Not doing this results in old parent directory being
	 * impossible to delete after log replay (rmdir will always fail with
	 * error -ENOTEMPTY).
	 *
	 * Example 1:
	 *
	 * mkdir testdir
	 * touch testdir/foo
	 * ln testdir/foo testdir/bar
	 * sync
	 * unlink testdir/bar
	 * xfs_io -c fsync testdir/foo
	 * <power failure>
	 * mount fs, triggers log replay
	 *
	 * If we don't log the parent directory (testdir), after log replay the
	 * directory still has an entry pointing to the file inode using the bar
	 * name, but a matching BTRFS_INODE_[REF|EXTREF]_KEY does not exist and
	 * the file inode has a link count of 1.
	 *
	 * Example 2:
	 *
	 * mkdir testdir
	 * touch foo
	 * ln foo testdir/foo2
	 * ln foo testdir/foo3
	 * sync
	 * unlink testdir/foo3
	 * xfs_io -c fsync foo
	 * <power failure>
	 * mount fs, triggers log replay
	 *
	 * Similar as the first example, after log replay the parent directory
	 * testdir still has an entry pointing to the inode file with name foo3
	 * but the file inode does not have a matching BTRFS_INODE_REF_KEY item
	 * and has a link count of 2.
	 */
	if (inode->last_unlink_trans > last_committed) {
		ret = btrfs_log_all_parents(trans, inode, ctx);
		if (ret)
			goto end_trans;
	}

	ret = log_all_new_ancestors(trans, inode, parent, ctx);
	if (ret)
		goto end_trans;

	if (log_dentries)
		ret = log_new_dir_dentries(trans, root, inode, ctx);
	else
		ret = 0;
end_trans:
	if (ret < 0) {
		btrfs_set_log_full_commit(trans);
		ret = 1;
	}

	if (ret)
		btrfs_remove_log_ctx(root, ctx);
	btrfs_end_log_trans(root);
end_no_trans:
	return ret;
}
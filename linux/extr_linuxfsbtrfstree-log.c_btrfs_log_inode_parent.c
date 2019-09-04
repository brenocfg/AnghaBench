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
struct dentry {struct super_block* d_sb; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_root {int /*<<< orphan*/  root_item; struct btrfs_fs_info* fs_info; } ;
struct btrfs_log_ctx {scalar_t__ log_new_dentries; } ;
struct TYPE_2__ {int i_nlink; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct btrfs_inode {scalar_t__ generation; scalar_t__ last_unlink_trans; scalar_t__ last_link_trans; struct btrfs_root* root; TYPE_1__ vfs_inode; } ;
struct btrfs_fs_info {scalar_t__ last_trans_committed; scalar_t__ last_trans_log_full_commit; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct btrfs_inode* BTRFS_I (int /*<<< orphan*/ ) ; 
 int BTRFS_NO_LOG_SYNC ; 
 int EMLINK ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  const LLONG_MAX ; 
 int LOG_INODE_EXISTS ; 
 int /*<<< orphan*/  NOTREELOG ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_log_trans (struct btrfs_root*) ; 
 scalar_t__ btrfs_inode_in_log (struct btrfs_inode*,int /*<<< orphan*/ ) ; 
 int btrfs_log_all_parents (struct btrfs_trans_handle*,struct btrfs_inode*,struct btrfs_log_ctx*) ; 
 int btrfs_log_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_inode*,int,int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct btrfs_log_ctx*) ; 
 int /*<<< orphan*/  btrfs_remove_log_ctx (struct btrfs_root*,struct btrfs_log_ctx*) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_set_log_full_commit (struct btrfs_fs_info*,struct btrfs_trans_handle*) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int check_parent_dirs_for_sync (struct btrfs_trans_handle*,struct btrfs_inode*,struct dentry*,struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
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
	struct dentry *old_parent = NULL;
	int ret = 0;
	u64 last_committed = fs_info->last_trans_committed;
	bool log_dentries = false;
	struct btrfs_inode *orig_inode = inode;

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
		ret = btrfs_log_all_parents(trans, orig_inode, ctx);
		if (ret)
			goto end_trans;
	}

	/*
	 * If a new hard link was added to the inode in the current transaction
	 * and its link count is now greater than 1, we need to fallback to a
	 * transaction commit, otherwise we can end up not logging all its new
	 * parents for all the hard links. Here just from the dentry used to
	 * fsync, we can not visit the ancestor inodes for all the other hard
	 * links to figure out if any is new, so we fallback to a transaction
	 * commit (instead of adding a lot of complexity of scanning a btree,
	 * since this scenario is not a common use case).
	 */
	if (inode->vfs_inode.i_nlink > 1 &&
	    inode->last_link_trans > last_committed) {
		ret = -EMLINK;
		goto end_trans;
	}

	while (1) {
		if (!parent || d_really_is_negative(parent) || sb != parent->d_sb)
			break;

		inode = BTRFS_I(d_inode(parent));
		if (root != inode->root)
			break;

		if (inode->generation > last_committed) {
			ret = btrfs_log_inode(trans, root, inode,
					LOG_INODE_EXISTS, 0, LLONG_MAX, ctx);
			if (ret)
				goto end_trans;
		}
		if (IS_ROOT(parent))
			break;

		parent = dget_parent(parent);
		dput(old_parent);
		old_parent = parent;
	}
	if (log_dentries)
		ret = log_new_dir_dentries(trans, root, orig_inode, ctx);
	else
		ret = 0;
end_trans:
	dput(old_parent);
	if (ret < 0) {
		btrfs_set_log_full_commit(fs_info, trans);
		ret = 1;
	}

	if (ret)
		btrfs_remove_log_ctx(root, ctx);
	btrfs_end_log_trans(root);
end_no_trans:
	return ret;
}
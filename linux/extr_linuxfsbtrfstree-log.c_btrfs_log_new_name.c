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
struct dentry {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; struct btrfs_fs_info* fs_info; } ;
struct btrfs_log_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;
struct btrfs_inode {scalar_t__ logged_trans; int /*<<< orphan*/  root; TYPE_1__ vfs_inode; int /*<<< orphan*/  last_unlink_trans; } ;
struct btrfs_fs_info {scalar_t__ last_trans_committed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_log_ctx*) ; 
 int BTRFS_DONT_NEED_LOG_SYNC ; 
 int BTRFS_DONT_NEED_TRANS_COMMIT ; 
 int BTRFS_NEED_LOG_SYNC ; 
 int BTRFS_NEED_TRANS_COMMIT ; 
 int BTRFS_NO_LOG_SYNC ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  LOG_INODE_EXISTS ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_init_log_ctx (struct btrfs_log_ctx*,TYPE_1__*) ; 
 int btrfs_log_inode_parent (struct btrfs_trans_handle*,struct btrfs_inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_log_ctx*) ; 
 int btrfs_sync_log (struct btrfs_trans_handle*,int /*<<< orphan*/ ,struct btrfs_log_ctx*) ; 

int btrfs_log_new_name(struct btrfs_trans_handle *trans,
			struct btrfs_inode *inode, struct btrfs_inode *old_dir,
			struct dentry *parent,
			bool sync_log, struct btrfs_log_ctx *ctx)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	int ret;

	/*
	 * this will force the logging code to walk the dentry chain
	 * up for the file
	 */
	if (!S_ISDIR(inode->vfs_inode.i_mode))
		inode->last_unlink_trans = trans->transid;

	/*
	 * if this inode hasn't been logged and directory we're renaming it
	 * from hasn't been logged, we don't need to log it
	 */
	if (inode->logged_trans <= fs_info->last_trans_committed &&
	    (!old_dir || old_dir->logged_trans <= fs_info->last_trans_committed))
		return sync_log ? BTRFS_DONT_NEED_TRANS_COMMIT :
			BTRFS_DONT_NEED_LOG_SYNC;

	if (sync_log) {
		struct btrfs_log_ctx ctx2;

		btrfs_init_log_ctx(&ctx2, &inode->vfs_inode);
		ret = btrfs_log_inode_parent(trans, inode, parent, 0, LLONG_MAX,
					     LOG_INODE_EXISTS, &ctx2);
		if (ret == BTRFS_NO_LOG_SYNC)
			return BTRFS_DONT_NEED_TRANS_COMMIT;
		else if (ret)
			return BTRFS_NEED_TRANS_COMMIT;

		ret = btrfs_sync_log(trans, inode->root, &ctx2);
		if (ret)
			return BTRFS_NEED_TRANS_COMMIT;
		return BTRFS_DONT_NEED_TRANS_COMMIT;
	}

	ASSERT(ctx);
	ret = btrfs_log_inode_parent(trans, inode, parent, 0, LLONG_MAX,
				     LOG_INODE_EXISTS, ctx);
	if (ret == BTRFS_NO_LOG_SYNC)
		return BTRFS_DONT_NEED_LOG_SYNC;
	else if (ret)
		return BTRFS_NEED_TRANS_COMMIT;

	return BTRFS_NEED_LOG_SYNC;
}
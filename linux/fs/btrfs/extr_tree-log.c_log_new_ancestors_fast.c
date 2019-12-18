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
struct dentry {struct super_block* d_sb; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_log_ctx {int dummy; } ;
struct TYPE_2__ {struct super_block* i_sb; } ;
struct btrfs_inode {scalar_t__ generation; struct btrfs_root* root; TYPE_1__ vfs_inode; } ;
struct btrfs_fs_info {scalar_t__ last_trans_committed; } ;

/* Variables and functions */
 struct btrfs_inode* BTRFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  LOG_INODE_EXISTS ; 
 int btrfs_log_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_log_ctx*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static int log_new_ancestors_fast(struct btrfs_trans_handle *trans,
				  struct btrfs_inode *inode,
				  struct dentry *parent,
				  struct btrfs_log_ctx *ctx)
{
	struct btrfs_root *root = inode->root;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct dentry *old_parent = NULL;
	struct super_block *sb = inode->vfs_inode.i_sb;
	int ret = 0;

	while (true) {
		if (!parent || d_really_is_negative(parent) ||
		    sb != parent->d_sb)
			break;

		inode = BTRFS_I(d_inode(parent));
		if (root != inode->root)
			break;

		if (inode->generation > fs_info->last_trans_committed) {
			ret = btrfs_log_inode(trans, root, inode,
					LOG_INODE_EXISTS, 0, LLONG_MAX, ctx);
			if (ret)
				break;
		}
		if (IS_ROOT(parent))
			break;

		parent = dget_parent(parent);
		dput(old_parent);
		old_parent = parent;
	}
	dput(old_parent);

	return ret;
}
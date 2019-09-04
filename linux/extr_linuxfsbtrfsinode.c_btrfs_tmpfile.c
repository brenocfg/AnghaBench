#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  u64 ;
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct btrfs_trans_handle {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_sb; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_8__ {TYPE_2__ io_tree; struct btrfs_root* root; } ;
struct TYPE_6__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  btrfs_aops ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct inode*) ; 
 int /*<<< orphan*/  btrfs_extent_io_ops ; 
 int /*<<< orphan*/  btrfs_file_inode_operations ; 
 int /*<<< orphan*/  btrfs_file_operations ; 
 int btrfs_find_free_ino (struct btrfs_root*,int /*<<< orphan*/ *) ; 
 int btrfs_init_inode_security (struct inode*,struct inode*,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_ino (TYPE_3__*) ; 
 struct inode* btrfs_new_inode (struct inode*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int btrfs_orphan_add (struct inode*,TYPE_3__*) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 struct inode* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_update_inode (struct inode*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  d_tmpfile (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  discard_new_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int btrfs_tmpfile(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct inode *inode = NULL;
	u64 objectid;
	u64 index;
	int ret = 0;

	/*
	 * 5 units required for adding orphan entry
	 */
	trans = btrfs_start_transaction(root, 5);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	ret = btrfs_find_free_ino(root, &objectid);
	if (ret)
		goto out;

	inode = btrfs_new_inode(trans, root, dir, NULL, 0,
			btrfs_ino(BTRFS_I(dir)), objectid, mode, &index);
	if (IS_ERR(inode)) {
		ret = PTR_ERR(inode);
		inode = NULL;
		goto out;
	}

	inode->i_fop = &btrfs_file_operations;
	inode->i_op = &btrfs_file_inode_operations;

	inode->i_mapping->a_ops = &btrfs_aops;
	BTRFS_I(inode)->io_tree.ops = &btrfs_extent_io_ops;

	ret = btrfs_init_inode_security(trans, inode, dir, NULL);
	if (ret)
		goto out;

	ret = btrfs_update_inode(trans, root, inode);
	if (ret)
		goto out;
	ret = btrfs_orphan_add(trans, BTRFS_I(inode));
	if (ret)
		goto out;

	/*
	 * We set number of links to 0 in btrfs_new_inode(), and here we set
	 * it to 1 because d_tmpfile() will issue a warning if the count is 0,
	 * through:
	 *
	 *    d_tmpfile() -> inode_dec_link_count() -> drop_nlink()
	 */
	set_nlink(inode, 1);
	d_tmpfile(dentry, inode);
	unlock_new_inode(inode);
	mark_inode_dirty(inode);
out:
	btrfs_end_transaction(trans);
	if (ret && inode)
		discard_new_inode(inode);
	btrfs_btree_balance_dirty(fs_info);
	return ret;
}
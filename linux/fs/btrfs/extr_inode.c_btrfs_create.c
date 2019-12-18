#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  u64 ;
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_sb; } ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_4__ d_name; } ;
struct btrfs_trans_handle {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_sb; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_10__ {TYPE_2__ io_tree; struct btrfs_root* root; } ;
struct TYPE_8__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int btrfs_add_nondir (struct inode*,TYPE_3__*,struct dentry*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_aops ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct inode*) ; 
 int /*<<< orphan*/  btrfs_extent_io_ops ; 
 int /*<<< orphan*/  btrfs_file_inode_operations ; 
 int /*<<< orphan*/  btrfs_file_operations ; 
 int btrfs_find_free_ino (struct btrfs_root*,int /*<<< orphan*/ *) ; 
 int btrfs_init_inode_security (struct inode*,struct inode*,struct inode*,TYPE_4__*) ; 
 int /*<<< orphan*/  btrfs_ino (TYPE_3__*) ; 
 struct inode* btrfs_new_inode (struct inode*,struct btrfs_root*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 struct inode* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_update_inode (struct inode*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  discard_new_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 

__attribute__((used)) static int btrfs_create(struct inode *dir, struct dentry *dentry,
			umode_t mode, bool excl)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(dir->i_sb);
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(dir)->root;
	struct inode *inode = NULL;
	int err;
	u64 objectid;
	u64 index = 0;

	/*
	 * 2 for inode item and ref
	 * 2 for dir items
	 * 1 for xattr if selinux is on
	 */
	trans = btrfs_start_transaction(root, 5);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	err = btrfs_find_free_ino(root, &objectid);
	if (err)
		goto out_unlock;

	inode = btrfs_new_inode(trans, root, dir, dentry->d_name.name,
			dentry->d_name.len, btrfs_ino(BTRFS_I(dir)), objectid,
			mode, &index);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		inode = NULL;
		goto out_unlock;
	}
	/*
	* If the active LSM wants to access the inode during
	* d_instantiate it needs these. Smack checks to see
	* if the filesystem supports xattrs by looking at the
	* ops vector.
	*/
	inode->i_fop = &btrfs_file_operations;
	inode->i_op = &btrfs_file_inode_operations;
	inode->i_mapping->a_ops = &btrfs_aops;

	err = btrfs_init_inode_security(trans, inode, dir, &dentry->d_name);
	if (err)
		goto out_unlock;

	err = btrfs_update_inode(trans, root, inode);
	if (err)
		goto out_unlock;

	err = btrfs_add_nondir(trans, BTRFS_I(dir), dentry, BTRFS_I(inode),
			0, index);
	if (err)
		goto out_unlock;

	BTRFS_I(inode)->io_tree.ops = &btrfs_extent_io_ops;
	d_instantiate_new(dentry, inode);

out_unlock:
	btrfs_end_transaction(trans);
	if (err && inode) {
		inode_dec_link_count(inode);
		discard_new_inode(inode);
	}
	btrfs_btree_balance_dirty(fs_info);
	return err;
}
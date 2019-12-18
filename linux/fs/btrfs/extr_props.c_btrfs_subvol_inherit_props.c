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
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_key {scalar_t__ offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct TYPE_2__ {struct super_block* sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FIRST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 struct inode* btrfs_iget (struct super_block*,struct btrfs_key*,struct btrfs_root*,int /*<<< orphan*/ *) ; 
 int inherit_props (struct btrfs_trans_handle*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

int btrfs_subvol_inherit_props(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root,
			       struct btrfs_root *parent_root)
{
	struct super_block *sb = root->fs_info->sb;
	struct btrfs_key key;
	struct inode *parent_inode, *child_inode;
	int ret;

	key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	parent_inode = btrfs_iget(sb, &key, parent_root, NULL);
	if (IS_ERR(parent_inode))
		return PTR_ERR(parent_inode);

	child_inode = btrfs_iget(sb, &key, root, NULL);
	if (IS_ERR(child_inode)) {
		iput(parent_inode);
		return PTR_ERR(child_inode);
	}

	ret = inherit_props(trans, child_inode, parent_inode);
	iput(child_inode);
	iput(parent_inode);

	return ret;
}
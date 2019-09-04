#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ offset; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; scalar_t__ i_size; } ;
struct btrfs_inode {TYPE_2__ vfs_inode; struct btrfs_root* root; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 scalar_t__ BTRFS_FIRST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_INODE_ITEM_KEY ; 
 int EEXIST ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int btrfs_add_root_ref (struct btrfs_trans_handle*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char const*,int) ; 
 int btrfs_del_inode_ref (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,scalar_t__,scalar_t__,scalar_t__*) ; 
 int btrfs_del_root_ref (struct btrfs_trans_handle*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,char const*,int) ; 
 int /*<<< orphan*/  btrfs_i_size_write (struct btrfs_inode*,scalar_t__) ; 
 scalar_t__ btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_inode_type (TYPE_2__*) ; 
 int btrfs_insert_dir_item (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,struct btrfs_inode*,struct btrfs_key*,int /*<<< orphan*/ ,scalar_t__) ; 
 int btrfs_insert_inode_ref (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,TYPE_2__*) ; 
 int /*<<< orphan*/  current_time (TYPE_2__*) ; 
 int /*<<< orphan*/  inode_inc_iversion (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_key*,TYPE_1__*,int) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_add_link(struct btrfs_trans_handle *trans,
		   struct btrfs_inode *parent_inode, struct btrfs_inode *inode,
		   const char *name, int name_len, int add_backref, u64 index)
{
	int ret = 0;
	struct btrfs_key key;
	struct btrfs_root *root = parent_inode->root;
	u64 ino = btrfs_ino(inode);
	u64 parent_ino = btrfs_ino(parent_inode);

	if (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) {
		memcpy(&key, &inode->root->root_key, sizeof(key));
	} else {
		key.objectid = ino;
		key.type = BTRFS_INODE_ITEM_KEY;
		key.offset = 0;
	}

	if (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) {
		ret = btrfs_add_root_ref(trans, key.objectid,
					 root->root_key.objectid, parent_ino,
					 index, name, name_len);
	} else if (add_backref) {
		ret = btrfs_insert_inode_ref(trans, root, name, name_len, ino,
					     parent_ino, index);
	}

	/* Nothing to clean up yet */
	if (ret)
		return ret;

	ret = btrfs_insert_dir_item(trans, root, name, name_len,
				    parent_inode, &key,
				    btrfs_inode_type(&inode->vfs_inode), index);
	if (ret == -EEXIST || ret == -EOVERFLOW)
		goto fail_dir_item;
	else if (ret) {
		btrfs_abort_transaction(trans, ret);
		return ret;
	}

	btrfs_i_size_write(parent_inode, parent_inode->vfs_inode.i_size +
			   name_len * 2);
	inode_inc_iversion(&parent_inode->vfs_inode);
	parent_inode->vfs_inode.i_mtime = parent_inode->vfs_inode.i_ctime =
		current_time(&parent_inode->vfs_inode);
	ret = btrfs_update_inode(trans, root, &parent_inode->vfs_inode);
	if (ret)
		btrfs_abort_transaction(trans, ret);
	return ret;

fail_dir_item:
	if (unlikely(ino == BTRFS_FIRST_FREE_OBJECTID)) {
		u64 local_index;
		int err;
		err = btrfs_del_root_ref(trans, key.objectid,
					 root->root_key.objectid, parent_ino,
					 &local_index, name, name_len);
		if (err)
			btrfs_abort_transaction(trans, err);
	} else if (add_backref) {
		u64 local_index;
		int err;

		err = btrfs_del_inode_ref(trans, root, name, name_len,
					  ino, parent_ino, &local_index);
		if (err)
			btrfs_abort_transaction(trans, err);
	}

	/* Return the original error code */
	return ret;
}
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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int /*<<< orphan*/  fs_info; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_inode {int /*<<< orphan*/  root; } ;
struct btrfs_delayed_node {int /*<<< orphan*/  mutex; int /*<<< orphan*/  inode_id; TYPE_1__* root; } ;
struct btrfs_delayed_item {struct btrfs_key key; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DIR_INDEX_KEY ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_delayed_node*) ; 
 int PTR_ERR (struct btrfs_delayed_node*) ; 
 int __btrfs_add_delayed_deletion_item (struct btrfs_delayed_node*,struct btrfs_delayed_item*) ; 
 struct btrfs_delayed_item* btrfs_alloc_delayed_item (int /*<<< orphan*/ ) ; 
 int btrfs_delayed_item_reserve_metadata (struct btrfs_trans_handle*,int /*<<< orphan*/ ,struct btrfs_delayed_item*) ; 
 int btrfs_delete_delayed_insertion_item (int /*<<< orphan*/ ,struct btrfs_delayed_node*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct btrfs_delayed_node* btrfs_get_or_create_delayed_node (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_delete_delayed_dir_index(struct btrfs_trans_handle *trans,
				   struct btrfs_inode *dir, u64 index)
{
	struct btrfs_delayed_node *node;
	struct btrfs_delayed_item *item;
	struct btrfs_key item_key;
	int ret;

	node = btrfs_get_or_create_delayed_node(dir);
	if (IS_ERR(node))
		return PTR_ERR(node);

	item_key.objectid = btrfs_ino(dir);
	item_key.type = BTRFS_DIR_INDEX_KEY;
	item_key.offset = index;

	ret = btrfs_delete_delayed_insertion_item(trans->fs_info, node,
						  &item_key);
	if (!ret)
		goto end;

	item = btrfs_alloc_delayed_item(0);
	if (!item) {
		ret = -ENOMEM;
		goto end;
	}

	item->key = item_key;

	ret = btrfs_delayed_item_reserve_metadata(trans, dir->root, item);
	/*
	 * we have reserved enough space when we start a new transaction,
	 * so reserving metadata failure is impossible.
	 */
	BUG_ON(ret);

	mutex_lock(&node->mutex);
	ret = __btrfs_add_delayed_deletion_item(node, item);
	if (unlikely(ret)) {
		btrfs_err(trans->fs_info,
			  "err add delayed dir index item(index: %llu) into the deletion tree of the delayed node(root id: %llu, inode id: %llu, errno: %d)",
			  index, node->root->objectid, node->inode_id, ret);
		BUG();
	}
	mutex_unlock(&node->mutex);
end:
	btrfs_release_delayed_node(node);
	return ret;
}
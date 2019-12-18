#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int /*<<< orphan*/  fs_info; int /*<<< orphan*/  transid; } ;
struct btrfs_inode {int /*<<< orphan*/  root; } ;
struct btrfs_disk_key {int dummy; } ;
struct btrfs_dir_item {struct btrfs_disk_key location; } ;
struct btrfs_delayed_node {int /*<<< orphan*/  mutex; int /*<<< orphan*/  inode_id; TYPE_3__* root; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_delayed_item {scalar_t__ data; TYPE_1__ key; } ;
struct TYPE_5__ {int /*<<< orphan*/  objectid; } ;
struct TYPE_6__ {TYPE_2__ root_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DIR_INDEX_KEY ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_delayed_node*) ; 
 int PTR_ERR (struct btrfs_delayed_node*) ; 
 int __btrfs_add_delayed_insertion_item (struct btrfs_delayed_node*,struct btrfs_delayed_item*) ; 
 struct btrfs_delayed_item* btrfs_alloc_delayed_item (int) ; 
 int btrfs_delayed_item_reserve_metadata (struct btrfs_trans_handle*,int /*<<< orphan*/ ,struct btrfs_delayed_item*) ; 
 int /*<<< orphan*/  btrfs_err (int /*<<< orphan*/ ,char*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct btrfs_delayed_node* btrfs_get_or_create_delayed_node (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_release_delayed_node (struct btrfs_delayed_node*) ; 
 int /*<<< orphan*/  btrfs_set_stack_dir_data_len (struct btrfs_dir_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_dir_name_len (struct btrfs_dir_item*,int) ; 
 int /*<<< orphan*/  btrfs_set_stack_dir_transid (struct btrfs_dir_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_dir_type (struct btrfs_dir_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_insert_delayed_dir_index(struct btrfs_trans_handle *trans,
				   const char *name, int name_len,
				   struct btrfs_inode *dir,
				   struct btrfs_disk_key *disk_key, u8 type,
				   u64 index)
{
	struct btrfs_delayed_node *delayed_node;
	struct btrfs_delayed_item *delayed_item;
	struct btrfs_dir_item *dir_item;
	int ret;

	delayed_node = btrfs_get_or_create_delayed_node(dir);
	if (IS_ERR(delayed_node))
		return PTR_ERR(delayed_node);

	delayed_item = btrfs_alloc_delayed_item(sizeof(*dir_item) + name_len);
	if (!delayed_item) {
		ret = -ENOMEM;
		goto release_node;
	}

	delayed_item->key.objectid = btrfs_ino(dir);
	delayed_item->key.type = BTRFS_DIR_INDEX_KEY;
	delayed_item->key.offset = index;

	dir_item = (struct btrfs_dir_item *)delayed_item->data;
	dir_item->location = *disk_key;
	btrfs_set_stack_dir_transid(dir_item, trans->transid);
	btrfs_set_stack_dir_data_len(dir_item, 0);
	btrfs_set_stack_dir_name_len(dir_item, name_len);
	btrfs_set_stack_dir_type(dir_item, type);
	memcpy((char *)(dir_item + 1), name, name_len);

	ret = btrfs_delayed_item_reserve_metadata(trans, dir->root, delayed_item);
	/*
	 * we have reserved enough space when we start a new transaction,
	 * so reserving metadata failure is impossible
	 */
	BUG_ON(ret);

	mutex_lock(&delayed_node->mutex);
	ret = __btrfs_add_delayed_insertion_item(delayed_node, delayed_item);
	if (unlikely(ret)) {
		btrfs_err(trans->fs_info,
			  "err add delayed dir index item(name: %.*s) into the insertion tree of the delayed node(root id: %llu, inode id: %llu, errno: %d)",
			  name_len, name, delayed_node->root->root_key.objectid,
			  delayed_node->inode_id, ret);
		BUG();
	}
	mutex_unlock(&delayed_node->mutex);

release_node:
	btrfs_release_delayed_node(delayed_node);
	return ret;
}
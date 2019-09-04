#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct btrfs_delayed_node {int /*<<< orphan*/  refs; int /*<<< orphan*/  mutex; } ;
struct btrfs_delayed_item {int /*<<< orphan*/  readdir_list; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 struct btrfs_delayed_item* __btrfs_first_delayed_deletion_item (struct btrfs_delayed_node*) ; 
 struct btrfs_delayed_item* __btrfs_first_delayed_insertion_item (struct btrfs_delayed_node*) ; 
 struct btrfs_delayed_item* __btrfs_next_delayed_item (struct btrfs_delayed_item*) ; 
 struct btrfs_delayed_node* btrfs_get_delayed_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

bool btrfs_readdir_get_delayed_items(struct inode *inode,
				     struct list_head *ins_list,
				     struct list_head *del_list)
{
	struct btrfs_delayed_node *delayed_node;
	struct btrfs_delayed_item *item;

	delayed_node = btrfs_get_delayed_node(BTRFS_I(inode));
	if (!delayed_node)
		return false;

	/*
	 * We can only do one readdir with delayed items at a time because of
	 * item->readdir_list.
	 */
	inode_unlock_shared(inode);
	inode_lock(inode);

	mutex_lock(&delayed_node->mutex);
	item = __btrfs_first_delayed_insertion_item(delayed_node);
	while (item) {
		refcount_inc(&item->refs);
		list_add_tail(&item->readdir_list, ins_list);
		item = __btrfs_next_delayed_item(item);
	}

	item = __btrfs_first_delayed_deletion_item(delayed_node);
	while (item) {
		refcount_inc(&item->refs);
		list_add_tail(&item->readdir_list, del_list);
		item = __btrfs_next_delayed_item(item);
	}
	mutex_unlock(&delayed_node->mutex);
	/*
	 * This delayed node is still cached in the btrfs inode, so refs
	 * must be > 1 now, and we needn't check it is going to be freed
	 * or not.
	 *
	 * Besides that, this function is used to read dir, we do not
	 * insert/delete delayed items in this period. So we also needn't
	 * requeue or dequeue this delayed node.
	 */
	refcount_dec(&delayed_node->refs);

	return true;
}
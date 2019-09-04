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
struct rb_node {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_transaction {int /*<<< orphan*/  pending_wait; int /*<<< orphan*/  pending_ordered; int /*<<< orphan*/  use_count; } ;
struct btrfs_root {int /*<<< orphan*/  ordered_extent_lock; int /*<<< orphan*/  ordered_root; int /*<<< orphan*/  nr_ordered_extents; } ;
struct btrfs_ordered_inode_tree {int /*<<< orphan*/  lock; struct rb_node* last; int /*<<< orphan*/  tree; } ;
struct btrfs_ordered_extent {int /*<<< orphan*/  wait; int /*<<< orphan*/  root_extent_list; int /*<<< orphan*/  flags; struct rb_node rb_node; int /*<<< orphan*/  len; } ;
struct btrfs_inode {struct btrfs_ordered_inode_tree ordered_tree; int /*<<< orphan*/  lock; struct btrfs_root* root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  ordered_root_lock; int /*<<< orphan*/  trans_lock; struct btrfs_transaction* running_transaction; struct btrfs_root* tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct btrfs_transaction*) ; 
 struct btrfs_inode* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_ORDERED_COMPLETE ; 
 int /*<<< orphan*/  BTRFS_ORDERED_PENDING ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (struct rb_node*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_delalloc_release_metadata (struct btrfs_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (struct btrfs_inode*,int) ; 
 int /*<<< orphan*/  btrfs_put_transaction (struct btrfs_transaction*) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_ordered_extent_remove (struct inode*,struct btrfs_ordered_extent*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void btrfs_remove_ordered_extent(struct inode *inode,
				 struct btrfs_ordered_extent *entry)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_ordered_inode_tree *tree;
	struct btrfs_inode *btrfs_inode = BTRFS_I(inode);
	struct btrfs_root *root = btrfs_inode->root;
	struct rb_node *node;
	bool dec_pending_ordered = false;

	/* This is paired with btrfs_add_ordered_extent. */
	spin_lock(&btrfs_inode->lock);
	btrfs_mod_outstanding_extents(btrfs_inode, -1);
	spin_unlock(&btrfs_inode->lock);
	if (root != fs_info->tree_root)
		btrfs_delalloc_release_metadata(btrfs_inode, entry->len, false);

	tree = &btrfs_inode->ordered_tree;
	spin_lock_irq(&tree->lock);
	node = &entry->rb_node;
	rb_erase(node, &tree->tree);
	RB_CLEAR_NODE(node);
	if (tree->last == node)
		tree->last = NULL;
	set_bit(BTRFS_ORDERED_COMPLETE, &entry->flags);
	if (test_and_clear_bit(BTRFS_ORDERED_PENDING, &entry->flags))
		dec_pending_ordered = true;
	spin_unlock_irq(&tree->lock);

	/*
	 * The current running transaction is waiting on us, we need to let it
	 * know that we're complete and wake it up.
	 */
	if (dec_pending_ordered) {
		struct btrfs_transaction *trans;

		/*
		 * The checks for trans are just a formality, it should be set,
		 * but if it isn't we don't want to deref/assert under the spin
		 * lock, so be nice and check if trans is set, but ASSERT() so
		 * if it isn't set a developer will notice.
		 */
		spin_lock(&fs_info->trans_lock);
		trans = fs_info->running_transaction;
		if (trans)
			refcount_inc(&trans->use_count);
		spin_unlock(&fs_info->trans_lock);

		ASSERT(trans);
		if (trans) {
			if (atomic_dec_and_test(&trans->pending_ordered))
				wake_up(&trans->pending_wait);
			btrfs_put_transaction(trans);
		}
	}

	spin_lock(&root->ordered_extent_lock);
	list_del_init(&entry->root_extent_list);
	root->nr_ordered_extents--;

	trace_btrfs_ordered_extent_remove(inode, entry);

	if (!root->nr_ordered_extents) {
		spin_lock(&fs_info->ordered_root_lock);
		BUG_ON(list_empty(&root->ordered_root));
		list_del_init(&root->ordered_root);
		spin_unlock(&fs_info->ordered_root_lock);
	}
	spin_unlock(&root->ordered_extent_lock);
	wake_up(&entry->wait);
}
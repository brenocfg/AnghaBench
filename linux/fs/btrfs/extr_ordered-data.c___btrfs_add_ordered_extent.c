#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct rb_node {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_root {int nr_ordered_extents; int /*<<< orphan*/  ordered_extent_lock; int /*<<< orphan*/  ordered_root; int /*<<< orphan*/  ordered_extents; } ;
struct btrfs_ordered_inode_tree {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct btrfs_ordered_extent {int compress_type; int /*<<< orphan*/  root_extent_list; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  trans_list; int /*<<< orphan*/  log_list; int /*<<< orphan*/  completion; int /*<<< orphan*/  work_list; int /*<<< orphan*/  list; int /*<<< orphan*/  wait; int /*<<< orphan*/  refs; int /*<<< orphan*/  flags; void* truncated_len; int /*<<< orphan*/  inode; void* bytes_left; void* disk_len; void* len; void* start; void* file_offset; } ;
struct btrfs_fs_info {int /*<<< orphan*/  ordered_root_lock; int /*<<< orphan*/  ordered_roots; int /*<<< orphan*/  delalloc_batch; int /*<<< orphan*/  dio_bytes; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct btrfs_ordered_inode_tree ordered_tree; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_ORDERED_COMPLETE ; 
 int BTRFS_ORDERED_DIRECT ; 
 int BTRFS_ORDERED_IO_DONE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_mod_outstanding_extents (TYPE_1__*,int) ; 
 int /*<<< orphan*/  btrfs_ordered_extent_cache ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct btrfs_ordered_extent* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_data_tree_panic (struct inode*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  percpu_counter_add_batch (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_ordered_extent_add (struct inode*,struct btrfs_ordered_extent*) ; 
 struct rb_node* tree_insert (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __btrfs_add_ordered_extent(struct inode *inode, u64 file_offset,
				      u64 start, u64 len, u64 disk_len,
				      int type, int dio, int compress_type)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_ordered_inode_tree *tree;
	struct rb_node *node;
	struct btrfs_ordered_extent *entry;

	tree = &BTRFS_I(inode)->ordered_tree;
	entry = kmem_cache_zalloc(btrfs_ordered_extent_cache, GFP_NOFS);
	if (!entry)
		return -ENOMEM;

	entry->file_offset = file_offset;
	entry->start = start;
	entry->len = len;
	entry->disk_len = disk_len;
	entry->bytes_left = len;
	entry->inode = igrab(inode);
	entry->compress_type = compress_type;
	entry->truncated_len = (u64)-1;
	if (type != BTRFS_ORDERED_IO_DONE && type != BTRFS_ORDERED_COMPLETE)
		set_bit(type, &entry->flags);

	if (dio) {
		percpu_counter_add_batch(&fs_info->dio_bytes, len,
					 fs_info->delalloc_batch);
		set_bit(BTRFS_ORDERED_DIRECT, &entry->flags);
	}

	/* one ref for the tree */
	refcount_set(&entry->refs, 1);
	init_waitqueue_head(&entry->wait);
	INIT_LIST_HEAD(&entry->list);
	INIT_LIST_HEAD(&entry->root_extent_list);
	INIT_LIST_HEAD(&entry->work_list);
	init_completion(&entry->completion);
	INIT_LIST_HEAD(&entry->log_list);
	INIT_LIST_HEAD(&entry->trans_list);

	trace_btrfs_ordered_extent_add(inode, entry);

	spin_lock_irq(&tree->lock);
	node = tree_insert(&tree->tree, file_offset,
			   &entry->rb_node);
	if (node)
		ordered_data_tree_panic(inode, -EEXIST, file_offset);
	spin_unlock_irq(&tree->lock);

	spin_lock(&root->ordered_extent_lock);
	list_add_tail(&entry->root_extent_list,
		      &root->ordered_extents);
	root->nr_ordered_extents++;
	if (root->nr_ordered_extents == 1) {
		spin_lock(&fs_info->ordered_root_lock);
		BUG_ON(!list_empty(&root->ordered_root));
		list_add_tail(&root->ordered_root, &fs_info->ordered_roots);
		spin_unlock(&fs_info->ordered_root_lock);
	}
	spin_unlock(&root->ordered_extent_lock);

	/*
	 * We don't need the count_max_extents here, we can assume that all of
	 * that work has been done at higher layers, so this is truly the
	 * smallest the extent is going to get.
	 */
	spin_lock(&BTRFS_I(inode)->lock);
	btrfs_mod_outstanding_extents(BTRFS_I(inode), 1);
	spin_unlock(&BTRFS_I(inode)->lock);

	return 0;
}
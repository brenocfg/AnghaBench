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
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {int log_transid_committed; int /*<<< orphan*/  swapped_blocks; int /*<<< orphan*/  root_item_lock; scalar_t__ anon_dev; TYPE_1__ root_key; scalar_t__ defrag_trans_start; TYPE_1__ defrag_progress; TYPE_1__ root_item; int /*<<< orphan*/  dirty_log_pages; scalar_t__ last_log_commit; scalar_t__ log_transid; int /*<<< orphan*/  nr_swapfiles; int /*<<< orphan*/  snapshot_force_cow; int /*<<< orphan*/  will_be_snapshotted; int /*<<< orphan*/  refs; int /*<<< orphan*/  log_batch; int /*<<< orphan*/  log_writers; int /*<<< orphan*/ * log_commit; int /*<<< orphan*/ * log_ctxs; int /*<<< orphan*/ * log_commit_wait; int /*<<< orphan*/  log_writer_wait; int /*<<< orphan*/  delalloc_mutex; int /*<<< orphan*/  ordered_extent_mutex; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  objectid_mutex; int /*<<< orphan*/  qgroup_meta_rsv_lock; int /*<<< orphan*/ * log_extents_lock; int /*<<< orphan*/  accounting_lock; int /*<<< orphan*/  ordered_extent_lock; int /*<<< orphan*/  delalloc_lock; int /*<<< orphan*/  inode_lock; int /*<<< orphan*/ * logged_list; int /*<<< orphan*/  reloc_dirty_list; int /*<<< orphan*/  ordered_root; int /*<<< orphan*/  ordered_extents; int /*<<< orphan*/  delalloc_root; int /*<<< orphan*/  delalloc_inodes; int /*<<< orphan*/  root_list; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  delayed_nodes_tree; int /*<<< orphan*/  inode_tree; scalar_t__ nr_ordered_extents; scalar_t__ nr_delalloc_inodes; scalar_t__ highest_objectid; scalar_t__ last_trans; scalar_t__ orphan_cleanup_state; scalar_t__ state; int /*<<< orphan*/ * commit_root; int /*<<< orphan*/ * node; } ;
struct btrfs_fs_info {scalar_t__ generation; int /*<<< orphan*/  fs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_STATE_DUMMY_FS_INFO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_TREE_ROOT_DIRTY_LOG_PAGES ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_qgroup_init_swapped_blocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_io_tree_init (struct btrfs_fs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __setup_root(struct btrfs_root *root, struct btrfs_fs_info *fs_info,
			 u64 objectid)
{
	bool dummy = test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state);
	root->node = NULL;
	root->commit_root = NULL;
	root->state = 0;
	root->orphan_cleanup_state = 0;

	root->last_trans = 0;
	root->highest_objectid = 0;
	root->nr_delalloc_inodes = 0;
	root->nr_ordered_extents = 0;
	root->inode_tree = RB_ROOT;
	INIT_RADIX_TREE(&root->delayed_nodes_tree, GFP_ATOMIC);
	root->block_rsv = NULL;

	INIT_LIST_HEAD(&root->dirty_list);
	INIT_LIST_HEAD(&root->root_list);
	INIT_LIST_HEAD(&root->delalloc_inodes);
	INIT_LIST_HEAD(&root->delalloc_root);
	INIT_LIST_HEAD(&root->ordered_extents);
	INIT_LIST_HEAD(&root->ordered_root);
	INIT_LIST_HEAD(&root->reloc_dirty_list);
	INIT_LIST_HEAD(&root->logged_list[0]);
	INIT_LIST_HEAD(&root->logged_list[1]);
	spin_lock_init(&root->inode_lock);
	spin_lock_init(&root->delalloc_lock);
	spin_lock_init(&root->ordered_extent_lock);
	spin_lock_init(&root->accounting_lock);
	spin_lock_init(&root->log_extents_lock[0]);
	spin_lock_init(&root->log_extents_lock[1]);
	spin_lock_init(&root->qgroup_meta_rsv_lock);
	mutex_init(&root->objectid_mutex);
	mutex_init(&root->log_mutex);
	mutex_init(&root->ordered_extent_mutex);
	mutex_init(&root->delalloc_mutex);
	init_waitqueue_head(&root->log_writer_wait);
	init_waitqueue_head(&root->log_commit_wait[0]);
	init_waitqueue_head(&root->log_commit_wait[1]);
	INIT_LIST_HEAD(&root->log_ctxs[0]);
	INIT_LIST_HEAD(&root->log_ctxs[1]);
	atomic_set(&root->log_commit[0], 0);
	atomic_set(&root->log_commit[1], 0);
	atomic_set(&root->log_writers, 0);
	atomic_set(&root->log_batch, 0);
	refcount_set(&root->refs, 1);
	atomic_set(&root->will_be_snapshotted, 0);
	atomic_set(&root->snapshot_force_cow, 0);
	atomic_set(&root->nr_swapfiles, 0);
	root->log_transid = 0;
	root->log_transid_committed = -1;
	root->last_log_commit = 0;
	if (!dummy)
		extent_io_tree_init(fs_info, &root->dirty_log_pages,
				    IO_TREE_ROOT_DIRTY_LOG_PAGES, NULL);

	memset(&root->root_key, 0, sizeof(root->root_key));
	memset(&root->root_item, 0, sizeof(root->root_item));
	memset(&root->defrag_progress, 0, sizeof(root->defrag_progress));
	if (!dummy)
		root->defrag_trans_start = fs_info->generation;
	else
		root->defrag_trans_start = 0;
	root->root_key.objectid = objectid;
	root->anon_dev = 0;

	spin_lock_init(&root->root_item_lock);
	btrfs_qgroup_init_swapped_blocks(&root->swapped_blocks);
}
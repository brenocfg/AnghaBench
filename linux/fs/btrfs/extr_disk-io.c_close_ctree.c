#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bio_counter; } ;
struct btrfs_fs_info {int /*<<< orphan*/  subvol_srcu; TYPE_1__ dev_replace; int /*<<< orphan*/  dio_bytes; int /*<<< orphan*/  delalloc_bytes; int /*<<< orphan*/  dirty_metadata_bytes; int /*<<< orphan*/  fs_devices; int /*<<< orphan*/  mapping_tree; TYPE_2__* btree_inode; int /*<<< orphan*/  flags; int /*<<< orphan*/  delalloc_roots; int /*<<< orphan*/  delayed_iputs; int /*<<< orphan*/  cleaner_kthread; int /*<<< orphan*/  transaction_kthread; int /*<<< orphan*/  fs_state; int /*<<< orphan*/  sb; int /*<<< orphan*/  async_reclaim_work; int /*<<< orphan*/  defrag_running; int /*<<< orphan*/  transaction_wait; int /*<<< orphan*/  uuid_tree_rescan_sem; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTRFS_FS_CLOSING_DONE ; 
 int /*<<< orphan*/  BTRFS_FS_CLOSING_START ; 
 int /*<<< orphan*/  BTRFS_FS_OPEN ; 
 int /*<<< orphan*/  BTRFS_FS_STATE_ERROR ; 
 int /*<<< orphan*/  BTRFS_FS_STATE_TRANS_ABORTED ; 
 int /*<<< orphan*/  CHECK_INTEGRITY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_cleanup_defrag_inodes (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_close_devices (int /*<<< orphan*/ ) ; 
 int btrfs_commit_super (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_delete_unused_bgs (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_dev_replace_suspend_for_unmount (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,int) ; 
 int /*<<< orphan*/  btrfs_error_commit_super (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_block_groups (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_csum_hash (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_fs_roots (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_qgroup_config (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_ref_cache (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_stripe_hash_table (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_mapping_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_pause_balance (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_put_block_group_cache (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_qgroup_wait_for_completion (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  btrfs_scrub_cancel (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_stop_all_workers (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_sysfs_remove_fsid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_sysfs_remove_mounted (struct btrfs_fs_info*) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfsic_unmount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_root_pointers (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (TYPE_2__*) ; 
 int /*<<< orphan*/  kthread_park (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_rdonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void close_ctree(struct btrfs_fs_info *fs_info)
{
	int ret;

	set_bit(BTRFS_FS_CLOSING_START, &fs_info->flags);
	/*
	 * We don't want the cleaner to start new transactions, add more delayed
	 * iputs, etc. while we're closing. We can't use kthread_stop() yet
	 * because that frees the task_struct, and the transaction kthread might
	 * still try to wake up the cleaner.
	 */
	kthread_park(fs_info->cleaner_kthread);

	/* wait for the qgroup rescan worker to stop */
	btrfs_qgroup_wait_for_completion(fs_info, false);

	/* wait for the uuid_scan task to finish */
	down(&fs_info->uuid_tree_rescan_sem);
	/* avoid complains from lockdep et al., set sem back to initial state */
	up(&fs_info->uuid_tree_rescan_sem);

	/* pause restriper - we want to resume on mount */
	btrfs_pause_balance(fs_info);

	btrfs_dev_replace_suspend_for_unmount(fs_info);

	btrfs_scrub_cancel(fs_info);

	/* wait for any defraggers to finish */
	wait_event(fs_info->transaction_wait,
		   (atomic_read(&fs_info->defrag_running) == 0));

	/* clear out the rbtree of defraggable inodes */
	btrfs_cleanup_defrag_inodes(fs_info);

	cancel_work_sync(&fs_info->async_reclaim_work);

	if (!sb_rdonly(fs_info->sb)) {
		/*
		 * The cleaner kthread is stopped, so do one final pass over
		 * unused block groups.
		 */
		btrfs_delete_unused_bgs(fs_info);

		ret = btrfs_commit_super(fs_info);
		if (ret)
			btrfs_err(fs_info, "commit super ret %d", ret);
	}

	if (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state) ||
	    test_bit(BTRFS_FS_STATE_TRANS_ABORTED, &fs_info->fs_state))
		btrfs_error_commit_super(fs_info);

	kthread_stop(fs_info->transaction_kthread);
	kthread_stop(fs_info->cleaner_kthread);

	ASSERT(list_empty(&fs_info->delayed_iputs));
	set_bit(BTRFS_FS_CLOSING_DONE, &fs_info->flags);

	btrfs_free_qgroup_config(fs_info);
	ASSERT(list_empty(&fs_info->delalloc_roots));

	if (percpu_counter_sum(&fs_info->delalloc_bytes)) {
		btrfs_info(fs_info, "at unmount delalloc count %lld",
		       percpu_counter_sum(&fs_info->delalloc_bytes));
	}

	if (percpu_counter_sum(&fs_info->dio_bytes))
		btrfs_info(fs_info, "at unmount dio bytes count %lld",
			   percpu_counter_sum(&fs_info->dio_bytes));

	btrfs_sysfs_remove_mounted(fs_info);
	btrfs_sysfs_remove_fsid(fs_info->fs_devices);

	btrfs_free_fs_roots(fs_info);

	btrfs_put_block_group_cache(fs_info);

	/*
	 * we must make sure there is not any read request to
	 * submit after we stopping all workers.
	 */
	invalidate_inode_pages2(fs_info->btree_inode->i_mapping);
	btrfs_stop_all_workers(fs_info);

	btrfs_free_block_groups(fs_info);

	clear_bit(BTRFS_FS_OPEN, &fs_info->flags);
	free_root_pointers(fs_info, 1);

	iput(fs_info->btree_inode);

#ifdef CONFIG_BTRFS_FS_CHECK_INTEGRITY
	if (btrfs_test_opt(fs_info, CHECK_INTEGRITY))
		btrfsic_unmount(fs_info->fs_devices);
#endif

	btrfs_mapping_tree_free(&fs_info->mapping_tree);
	btrfs_close_devices(fs_info->fs_devices);

	percpu_counter_destroy(&fs_info->dirty_metadata_bytes);
	percpu_counter_destroy(&fs_info->delalloc_bytes);
	percpu_counter_destroy(&fs_info->dio_bytes);
	percpu_counter_destroy(&fs_info->dev_replace.bio_counter);
	cleanup_srcu_struct(&fs_info->subvol_srcu);

	btrfs_free_csum_hash(fs_info);
	btrfs_free_stripe_hash_table(fs_info);
	btrfs_free_ref_cache(fs_info);
}
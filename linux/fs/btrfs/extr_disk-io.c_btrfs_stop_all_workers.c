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
struct btrfs_fs_info {int /*<<< orphan*/  endio_meta_write_workers; int /*<<< orphan*/  endio_meta_workers; int /*<<< orphan*/  qgroup_rescan_workers; int /*<<< orphan*/  flush_workers; int /*<<< orphan*/  readahead_workers; int /*<<< orphan*/  caching_workers; int /*<<< orphan*/  delayed_workers; int /*<<< orphan*/  submit_workers; int /*<<< orphan*/  endio_freespace_worker; int /*<<< orphan*/  endio_write_workers; int /*<<< orphan*/  rmw_workers; int /*<<< orphan*/  endio_repair_workers; int /*<<< orphan*/  endio_raid56_workers; int /*<<< orphan*/  endio_workers; int /*<<< orphan*/  workers; int /*<<< orphan*/  delalloc_workers; int /*<<< orphan*/  fixup_workers; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_destroy_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btrfs_stop_all_workers(struct btrfs_fs_info *fs_info)
{
	btrfs_destroy_workqueue(fs_info->fixup_workers);
	btrfs_destroy_workqueue(fs_info->delalloc_workers);
	btrfs_destroy_workqueue(fs_info->workers);
	btrfs_destroy_workqueue(fs_info->endio_workers);
	btrfs_destroy_workqueue(fs_info->endio_raid56_workers);
	btrfs_destroy_workqueue(fs_info->endio_repair_workers);
	btrfs_destroy_workqueue(fs_info->rmw_workers);
	btrfs_destroy_workqueue(fs_info->endio_write_workers);
	btrfs_destroy_workqueue(fs_info->endio_freespace_worker);
	btrfs_destroy_workqueue(fs_info->submit_workers);
	btrfs_destroy_workqueue(fs_info->delayed_workers);
	btrfs_destroy_workqueue(fs_info->caching_workers);
	btrfs_destroy_workqueue(fs_info->readahead_workers);
	btrfs_destroy_workqueue(fs_info->flush_workers);
	btrfs_destroy_workqueue(fs_info->qgroup_rescan_workers);
	/*
	 * Now that all other work queues are destroyed, we can safely destroy
	 * the queues used for metadata I/O, since tasks from those other work
	 * queues can do metadata I/O operations.
	 */
	btrfs_destroy_workqueue(fs_info->endio_meta_workers);
	btrfs_destroy_workqueue(fs_info->endio_meta_write_workers);
}
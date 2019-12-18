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
typedef  scalar_t__ u32 ;
struct btrfs_fs_info {int /*<<< orphan*/  scrub_wr_completion_workers; int /*<<< orphan*/  readahead_workers; int /*<<< orphan*/  delayed_workers; int /*<<< orphan*/  endio_freespace_worker; int /*<<< orphan*/  endio_write_workers; int /*<<< orphan*/  endio_meta_write_workers; int /*<<< orphan*/  endio_meta_workers; int /*<<< orphan*/  endio_workers; int /*<<< orphan*/  caching_workers; int /*<<< orphan*/  submit_workers; int /*<<< orphan*/  delalloc_workers; int /*<<< orphan*/  workers; scalar_t__ thread_pool_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_workqueue_set_max (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void btrfs_resize_thread_pool(struct btrfs_fs_info *fs_info,
				     u32 new_pool_size, u32 old_pool_size)
{
	if (new_pool_size == old_pool_size)
		return;

	fs_info->thread_pool_size = new_pool_size;

	btrfs_info(fs_info, "resize thread pool %d -> %d",
	       old_pool_size, new_pool_size);

	btrfs_workqueue_set_max(fs_info->workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->delalloc_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->submit_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->caching_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_meta_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_meta_write_workers,
				new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_write_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->endio_freespace_worker, new_pool_size);
	btrfs_workqueue_set_max(fs_info->delayed_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->readahead_workers, new_pool_size);
	btrfs_workqueue_set_max(fs_info->scrub_wr_completion_workers,
				new_pool_size);
}
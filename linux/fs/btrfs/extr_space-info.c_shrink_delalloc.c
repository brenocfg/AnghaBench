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
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_space_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  priority_tickets; int /*<<< orphan*/  tickets; } ;
struct btrfs_fs_info {int /*<<< orphan*/  dio_bytes; int /*<<< orphan*/  delalloc_bytes; int /*<<< orphan*/  async_delalloc_pages; int /*<<< orphan*/  async_submit_wait; } ;
struct TYPE_2__ {scalar_t__ journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_METADATA ; 
 scalar_t__ EXTENT_SIZE_PER_ITEM ; 
 unsigned long PAGE_SHIFT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct btrfs_space_info* btrfs_find_space_info (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_roots (struct btrfs_fs_info*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_writeback_inodes_sb_nr (struct btrfs_fs_info*,unsigned long,scalar_t__) ; 
 scalar_t__ calc_reclaim_items_nr (struct btrfs_fs_info*,scalar_t__) ; 
 TYPE_1__* current ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 unsigned long min (scalar_t__,scalar_t__) ; 
 scalar_t__ percpu_counter_sum_positive (int /*<<< orphan*/ *) ; 
 long schedule_timeout_killable (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void shrink_delalloc(struct btrfs_fs_info *fs_info, u64 to_reclaim,
			    u64 orig, bool wait_ordered)
{
	struct btrfs_space_info *space_info;
	struct btrfs_trans_handle *trans;
	u64 delalloc_bytes;
	u64 dio_bytes;
	u64 async_pages;
	u64 items;
	long time_left;
	unsigned long nr_pages;
	int loops;

	/* Calc the number of the pages we need flush for space reservation */
	items = calc_reclaim_items_nr(fs_info, to_reclaim);
	to_reclaim = items * EXTENT_SIZE_PER_ITEM;

	trans = (struct btrfs_trans_handle *)current->journal_info;
	space_info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_METADATA);

	delalloc_bytes = percpu_counter_sum_positive(
						&fs_info->delalloc_bytes);
	dio_bytes = percpu_counter_sum_positive(&fs_info->dio_bytes);
	if (delalloc_bytes == 0 && dio_bytes == 0) {
		if (trans)
			return;
		if (wait_ordered)
			btrfs_wait_ordered_roots(fs_info, items, 0, (u64)-1);
		return;
	}

	/*
	 * If we are doing more ordered than delalloc we need to just wait on
	 * ordered extents, otherwise we'll waste time trying to flush delalloc
	 * that likely won't give us the space back we need.
	 */
	if (dio_bytes > delalloc_bytes)
		wait_ordered = true;

	loops = 0;
	while ((delalloc_bytes || dio_bytes) && loops < 3) {
		nr_pages = min(delalloc_bytes, to_reclaim) >> PAGE_SHIFT;

		/*
		 * Triggers inode writeback for up to nr_pages. This will invoke
		 * ->writepages callback and trigger delalloc filling
		 *  (btrfs_run_delalloc_range()).
		 */
		btrfs_writeback_inodes_sb_nr(fs_info, nr_pages, items);

		/*
		 * We need to wait for the compressed pages to start before
		 * we continue.
		 */
		async_pages = atomic_read(&fs_info->async_delalloc_pages);
		if (!async_pages)
			goto skip_async;

		/*
		 * Calculate how many compressed pages we want to be written
		 * before we continue. I.e if there are more async pages than we
		 * require wait_event will wait until nr_pages are written.
		 */
		if (async_pages <= nr_pages)
			async_pages = 0;
		else
			async_pages -= nr_pages;

		wait_event(fs_info->async_submit_wait,
			   atomic_read(&fs_info->async_delalloc_pages) <=
			   (int)async_pages);
skip_async:
		spin_lock(&space_info->lock);
		if (list_empty(&space_info->tickets) &&
		    list_empty(&space_info->priority_tickets)) {
			spin_unlock(&space_info->lock);
			break;
		}
		spin_unlock(&space_info->lock);

		loops++;
		if (wait_ordered && !trans) {
			btrfs_wait_ordered_roots(fs_info, items, 0, (u64)-1);
		} else {
			time_left = schedule_timeout_killable(1);
			if (time_left)
				break;
		}
		delalloc_bytes = percpu_counter_sum_positive(
						&fs_info->delalloc_bytes);
		dio_bytes = percpu_counter_sum_positive(&fs_info->dio_bytes);
	}
}
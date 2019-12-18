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
typedef  int /*<<< orphan*/  u64 ;
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct btrfs_fs_info {struct extent_io_tree* freed_extents; int /*<<< orphan*/  unused_bg_unpin_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_DIRTY ; 
 int /*<<< orphan*/  btrfs_error_unpin_extent_range (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_extent_dirty (struct extent_io_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extent_state**) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int find_first_extent_bit (struct extent_io_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct extent_state**) ; 
 int /*<<< orphan*/  free_extent_state (struct extent_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_destroy_pinned_extent(struct btrfs_fs_info *fs_info,
				       struct extent_io_tree *pinned_extents)
{
	struct extent_io_tree *unpin;
	u64 start;
	u64 end;
	int ret;
	bool loop = true;

	unpin = pinned_extents;
again:
	while (1) {
		struct extent_state *cached_state = NULL;

		/*
		 * The btrfs_finish_extent_commit() may get the same range as
		 * ours between find_first_extent_bit and clear_extent_dirty.
		 * Hence, hold the unused_bg_unpin_mutex to avoid double unpin
		 * the same extent range.
		 */
		mutex_lock(&fs_info->unused_bg_unpin_mutex);
		ret = find_first_extent_bit(unpin, 0, &start, &end,
					    EXTENT_DIRTY, &cached_state);
		if (ret) {
			mutex_unlock(&fs_info->unused_bg_unpin_mutex);
			break;
		}

		clear_extent_dirty(unpin, start, end, &cached_state);
		free_extent_state(cached_state);
		btrfs_error_unpin_extent_range(fs_info, start, end);
		mutex_unlock(&fs_info->unused_bg_unpin_mutex);
		cond_resched();
	}

	if (loop) {
		if (unpin == &fs_info->freed_extents[0])
			unpin = &fs_info->freed_extents[1];
		else
			unpin = &fs_info->freed_extents[0];
		loop = false;
		goto again;
	}

	return 0;
}
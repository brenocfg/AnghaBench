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
struct extent_state {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct extent_buffer {scalar_t__ len; scalar_t__ start; int /*<<< orphan*/  fs_info; } ;
struct TYPE_2__ {scalar_t__ journal_info; } ;

/* Variables and functions */
 scalar_t__ BTRFS_SEND_TRANS_STUB ; 
 int EAGAIN ; 
 int /*<<< orphan*/  btrfs_err_rl (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking_read (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_read_unlock_blocking (struct extent_buffer*) ; 
 int /*<<< orphan*/  clear_extent_buffer_uptodate (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  extent_buffer_under_io (struct extent_buffer*) ; 
 scalar_t__ extent_buffer_uptodate (struct extent_buffer*) ; 
 int /*<<< orphan*/  lock_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**) ; 
 int /*<<< orphan*/  unlock_extent_cached (struct extent_io_tree*,scalar_t__,scalar_t__,struct extent_state**) ; 

__attribute__((used)) static int verify_parent_transid(struct extent_io_tree *io_tree,
				 struct extent_buffer *eb, u64 parent_transid,
				 int atomic)
{
	struct extent_state *cached_state = NULL;
	int ret;
	bool need_lock = (current->journal_info == BTRFS_SEND_TRANS_STUB);

	if (!parent_transid || btrfs_header_generation(eb) == parent_transid)
		return 0;

	if (atomic)
		return -EAGAIN;

	if (need_lock) {
		btrfs_tree_read_lock(eb);
		btrfs_set_lock_blocking_read(eb);
	}

	lock_extent_bits(io_tree, eb->start, eb->start + eb->len - 1,
			 &cached_state);
	if (extent_buffer_uptodate(eb) &&
	    btrfs_header_generation(eb) == parent_transid) {
		ret = 0;
		goto out;
	}
	btrfs_err_rl(eb->fs_info,
		"parent transid verify failed on %llu wanted %llu found %llu",
			eb->start,
			parent_transid, btrfs_header_generation(eb));
	ret = 1;

	/*
	 * Things reading via commit roots that don't have normal protection,
	 * like send, can have a really old block in cache that may point at a
	 * block that has been freed and re-allocated.  So don't clear uptodate
	 * if we find an eb that is under IO (dirty/writeback) because we could
	 * end up reading in the stale data and then writing it back out and
	 * making everybody very sad.
	 */
	if (!extent_buffer_under_io(eb))
		clear_extent_buffer_uptodate(eb);
out:
	unlock_extent_cached(io_tree, eb->start, eb->start + eb->len - 1,
			     &cached_state);
	if (need_lock)
		btrfs_tree_read_unlock_blocking(eb);
	return ret;
}
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
struct extent_buffer {int blocking_writers; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_lock_wq; scalar_t__ lock_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btrfs_assert_no_spinning_writers (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_spinning_writers_put (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_write_locks_put (struct extent_buffer*) ; 
 int /*<<< orphan*/  cond_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_tree_unlock (struct extent_buffer*) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_tree_unlock(struct extent_buffer *eb)
{
	int blockers = eb->blocking_writers;

	BUG_ON(blockers > 1);

	btrfs_assert_tree_locked(eb);
	trace_btrfs_tree_unlock(eb);
	eb->lock_owner = 0;
	btrfs_assert_tree_write_locks_put(eb);

	if (blockers) {
		btrfs_assert_no_spinning_writers(eb);
		eb->blocking_writers--;
		/*
		 * We need to order modifying blocking_writers above with
		 * actually waking up the sleepers to ensure they see the
		 * updated value of blocking_writers
		 */
		cond_wake_up(&eb->write_lock_wq);
	} else {
		btrfs_assert_spinning_writers_put(eb);
		write_unlock(&eb->lock);
	}
}
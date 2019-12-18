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
struct extent_buffer {int lock_nested; scalar_t__ lock_owner; int /*<<< orphan*/  read_lock_wq; int /*<<< orphan*/  blocking_readers; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locked (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locks_put (struct extent_buffer*) ; 
 int /*<<< orphan*/  cond_wake_up_nomb (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  trace_btrfs_tree_read_unlock_blocking (struct extent_buffer*) ; 

void btrfs_tree_read_unlock_blocking(struct extent_buffer *eb)
{
	trace_btrfs_tree_read_unlock_blocking(eb);
	/*
	 * if we're nested, we have the write lock.  No new locking
	 * is needed as long as we are the lock owner.
	 * The write unlock will do a barrier for us, and the lock_nested
	 * field only matters to the lock owner.
	 */
	if (eb->lock_nested && current->pid == eb->lock_owner) {
		eb->lock_nested = false;
		return;
	}
	btrfs_assert_tree_read_locked(eb);
	WARN_ON(atomic_read(&eb->blocking_readers) == 0);
	/* atomic_dec_and_test implies a barrier */
	if (atomic_dec_and_test(&eb->blocking_readers))
		cond_wake_up_nomb(&eb->read_lock_wq);
	btrfs_assert_tree_read_locks_put(eb);
}
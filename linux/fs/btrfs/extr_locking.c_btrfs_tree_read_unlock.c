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
struct extent_buffer {int lock_nested; scalar_t__ lock_owner; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_assert_spinning_readers_put (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locked (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locks_put (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_tree_read_unlock (struct extent_buffer*) ; 

void btrfs_tree_read_unlock(struct extent_buffer *eb)
{
	trace_btrfs_tree_read_unlock(eb);
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
	btrfs_assert_spinning_readers_put(eb);
	btrfs_assert_tree_read_locks_put(eb);
	read_unlock(&eb->lock);
}
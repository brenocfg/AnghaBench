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
struct extent_buffer {scalar_t__ lock_owner; scalar_t__ blocking_writers; int /*<<< orphan*/  lock; scalar_t__ lock_nested; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_assert_spinning_writers_put (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  trace_btrfs_set_lock_blocking_write (struct extent_buffer*) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_set_lock_blocking_write(struct extent_buffer *eb)
{
	trace_btrfs_set_lock_blocking_write(eb);
	/*
	 * No lock is required.  The lock owner may change if we have a read
	 * lock, but it won't change to or away from us.  If we have the write
	 * lock, we are the owner and it'll never change.
	 */
	if (eb->lock_nested && current->pid == eb->lock_owner)
		return;
	if (eb->blocking_writers == 0) {
		btrfs_assert_spinning_writers_put(eb);
		btrfs_assert_tree_locked(eb);
		eb->blocking_writers++;
		write_unlock(&eb->lock);
	}
}
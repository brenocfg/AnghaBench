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
struct extent_buffer {scalar_t__ lock_owner; int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_readers; scalar_t__ lock_nested; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assert_spinning_readers_put (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locked (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_set_lock_blocking_read (struct extent_buffer*) ; 

void btrfs_set_lock_blocking_read(struct extent_buffer *eb)
{
	trace_btrfs_set_lock_blocking_read(eb);
	/*
	 * No lock is required.  The lock owner may change if we have a read
	 * lock, but it won't change to or away from us.  If we have the write
	 * lock, we are the owner and it'll never change.
	 */
	if (eb->lock_nested && current->pid == eb->lock_owner)
		return;
	btrfs_assert_tree_read_locked(eb);
	atomic_inc(&eb->blocking_readers);
	btrfs_assert_spinning_readers_put(eb);
	read_unlock(&eb->lock);
}
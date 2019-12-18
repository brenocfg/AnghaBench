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
struct extent_buffer {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_readers; scalar_t__ blocking_writers; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assert_spinning_writers_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_write_locks_get (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  trace_btrfs_try_tree_write_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int btrfs_try_tree_write_lock(struct extent_buffer *eb)
{
	if (eb->blocking_writers || atomic_read(&eb->blocking_readers))
		return 0;

	write_lock(&eb->lock);
	if (eb->blocking_writers || atomic_read(&eb->blocking_readers)) {
		write_unlock(&eb->lock);
		return 0;
	}
	btrfs_assert_tree_write_locks_get(eb);
	btrfs_assert_spinning_writers_get(eb);
	eb->lock_owner = current->pid;
	trace_btrfs_try_tree_write_lock(eb);
	return 1;
}
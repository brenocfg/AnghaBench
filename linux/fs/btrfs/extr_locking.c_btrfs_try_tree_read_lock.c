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
struct extent_buffer {int /*<<< orphan*/  lock; scalar_t__ blocking_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_assert_spinning_readers_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locks_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_try_tree_read_lock (struct extent_buffer*) ; 

int btrfs_try_tree_read_lock(struct extent_buffer *eb)
{
	if (eb->blocking_writers)
		return 0;

	if (!read_trylock(&eb->lock))
		return 0;

	if (eb->blocking_writers) {
		read_unlock(&eb->lock);
		return 0;
	}
	btrfs_assert_tree_read_locks_get(eb);
	btrfs_assert_spinning_readers_get(eb);
	trace_btrfs_try_tree_read_lock(eb);
	return 1;
}
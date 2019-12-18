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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {scalar_t__ blocking_writers; scalar_t__ lock_owner; int lock_nested; int /*<<< orphan*/  write_lock_wq; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btrfs_assert_spinning_readers_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locks_get (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_tree_read_lock (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ trace_btrfs_tree_read_lock_enabled () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void btrfs_tree_read_lock(struct extent_buffer *eb)
{
	u64 start_ns = 0;

	if (trace_btrfs_tree_read_lock_enabled())
		start_ns = ktime_get_ns();
again:
	read_lock(&eb->lock);
	BUG_ON(eb->blocking_writers == 0 &&
	       current->pid == eb->lock_owner);
	if (eb->blocking_writers && current->pid == eb->lock_owner) {
		/*
		 * This extent is already write-locked by our thread. We allow
		 * an additional read lock to be added because it's for the same
		 * thread. btrfs_find_all_roots() depends on this as it may be
		 * called on a partly (write-)locked tree.
		 */
		BUG_ON(eb->lock_nested);
		eb->lock_nested = true;
		read_unlock(&eb->lock);
		trace_btrfs_tree_read_lock(eb, start_ns);
		return;
	}
	if (eb->blocking_writers) {
		read_unlock(&eb->lock);
		wait_event(eb->write_lock_wq,
			   eb->blocking_writers == 0);
		goto again;
	}
	btrfs_assert_tree_read_locks_get(eb);
	btrfs_assert_spinning_readers_get(eb);
	trace_btrfs_tree_read_lock(eb, start_ns);
}
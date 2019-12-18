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
struct extent_buffer {scalar_t__ lock_owner; scalar_t__ blocking_writers; int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  write_lock_wq; int /*<<< orphan*/  read_lock_wq; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assert_spinning_writers_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_assert_tree_write_locks_get (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  trace_btrfs_tree_lock (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ trace_btrfs_tree_lock_enabled () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_tree_lock(struct extent_buffer *eb)
{
	u64 start_ns = 0;

	if (trace_btrfs_tree_lock_enabled())
		start_ns = ktime_get_ns();

	WARN_ON(eb->lock_owner == current->pid);
again:
	wait_event(eb->read_lock_wq, atomic_read(&eb->blocking_readers) == 0);
	wait_event(eb->write_lock_wq, eb->blocking_writers == 0);
	write_lock(&eb->lock);
	if (atomic_read(&eb->blocking_readers) || eb->blocking_writers) {
		write_unlock(&eb->lock);
		goto again;
	}
	btrfs_assert_spinning_writers_get(eb);
	btrfs_assert_tree_write_locks_get(eb);
	eb->lock_owner = current->pid;
	trace_btrfs_tree_lock(eb, start_ns);
}
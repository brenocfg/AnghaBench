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
struct extent_buffer {scalar_t__ lock_owner; int /*<<< orphan*/  lock; int /*<<< orphan*/  read_locks; int /*<<< orphan*/  spinning_readers; scalar_t__ lock_nested; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assert_tree_read_locked (struct extent_buffer*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

void btrfs_tree_read_unlock(struct extent_buffer *eb)
{
	/*
	 * if we're nested, we have the write lock.  No new locking
	 * is needed as long as we are the lock owner.
	 * The write unlock will do a barrier for us, and the lock_nested
	 * field only matters to the lock owner.
	 */
	if (eb->lock_nested && current->pid == eb->lock_owner) {
		eb->lock_nested = 0;
		return;
	}
	btrfs_assert_tree_read_locked(eb);
	WARN_ON(atomic_read(&eb->spinning_readers) == 0);
	atomic_dec(&eb->spinning_readers);
	atomic_dec(&eb->read_locks);
	read_unlock(&eb->lock);
}
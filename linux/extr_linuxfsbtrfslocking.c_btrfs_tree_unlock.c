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
struct extent_buffer {int /*<<< orphan*/  lock; int /*<<< orphan*/  spinning_writers; int /*<<< orphan*/  write_lock_wq; int /*<<< orphan*/  blocking_writers; int /*<<< orphan*/  write_locks; scalar_t__ lock_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 int /*<<< orphan*/  cond_wake_up_nomb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_tree_unlock(struct extent_buffer *eb)
{
	int blockers = atomic_read(&eb->blocking_writers);

	BUG_ON(blockers > 1);

	btrfs_assert_tree_locked(eb);
	eb->lock_owner = 0;
	atomic_dec(&eb->write_locks);

	if (blockers) {
		WARN_ON(atomic_read(&eb->spinning_writers));
		atomic_dec(&eb->blocking_writers);
		/* Use the lighter barrier after atomic */
		smp_mb__after_atomic();
		cond_wake_up_nomb(&eb->write_lock_wq);
	} else {
		WARN_ON(atomic_read(&eb->spinning_writers) != 1);
		atomic_dec(&eb->spinning_writers);
		write_unlock(&eb->lock);
	}
}
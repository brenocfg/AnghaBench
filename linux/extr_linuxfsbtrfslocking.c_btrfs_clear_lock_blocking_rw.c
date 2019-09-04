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
struct extent_buffer {scalar_t__ lock_owner; int /*<<< orphan*/  read_lock_wq; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  spinning_readers; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_lock_wq; int /*<<< orphan*/  blocking_writers; int /*<<< orphan*/  spinning_writers; scalar_t__ lock_nested; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int BTRFS_READ_LOCK_BLOCKING ; 
 int BTRFS_WRITE_LOCK_BLOCKING ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_wake_up_nomb (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 

void btrfs_clear_lock_blocking_rw(struct extent_buffer *eb, int rw)
{
	/*
	 * no lock is required.  The lock owner may change if
	 * we have a read lock, but it won't change to or away
	 * from us.  If we have the write lock, we are the owner
	 * and it'll never change.
	 */
	if (eb->lock_nested && current->pid == eb->lock_owner)
		return;

	if (rw == BTRFS_WRITE_LOCK_BLOCKING) {
		BUG_ON(atomic_read(&eb->blocking_writers) != 1);
		write_lock(&eb->lock);
		WARN_ON(atomic_read(&eb->spinning_writers));
		atomic_inc(&eb->spinning_writers);
		/* atomic_dec_and_test implies a barrier */
		if (atomic_dec_and_test(&eb->blocking_writers))
			cond_wake_up_nomb(&eb->write_lock_wq);
	} else if (rw == BTRFS_READ_LOCK_BLOCKING) {
		BUG_ON(atomic_read(&eb->blocking_readers) == 0);
		read_lock(&eb->lock);
		atomic_inc(&eb->spinning_readers);
		/* atomic_dec_and_test implies a barrier */
		if (atomic_dec_and_test(&eb->blocking_readers))
			cond_wake_up_nomb(&eb->read_lock_wq);
	}
}
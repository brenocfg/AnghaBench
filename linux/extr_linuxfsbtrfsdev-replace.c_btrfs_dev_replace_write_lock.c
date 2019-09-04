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
struct btrfs_dev_replace {int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  read_lock_wq; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_dev_replace_write_lock(struct btrfs_dev_replace *dev_replace)
{
again:
	wait_event(dev_replace->read_lock_wq,
		   atomic_read(&dev_replace->blocking_readers) == 0);
	write_lock(&dev_replace->lock);
	if (atomic_read(&dev_replace->blocking_readers)) {
		write_unlock(&dev_replace->lock);
		goto again;
	}
}
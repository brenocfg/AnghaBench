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
struct btrfs_dev_replace {int /*<<< orphan*/  lock; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  read_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

void btrfs_dev_replace_set_lock_blocking(
					struct btrfs_dev_replace *dev_replace)
{
	/* only set blocking for read lock */
	ASSERT(atomic_read(&dev_replace->read_locks) > 0);
	atomic_inc(&dev_replace->blocking_readers);
	read_unlock(&dev_replace->lock);
}
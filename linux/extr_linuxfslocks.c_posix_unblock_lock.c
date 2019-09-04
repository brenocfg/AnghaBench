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
struct file_lock {scalar_t__ fl_next; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __locks_delete_block (struct file_lock*) ; 
 int /*<<< orphan*/  blocked_lock_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
posix_unblock_lock(struct file_lock *waiter)
{
	int status = 0;

	spin_lock(&blocked_lock_lock);
	if (waiter->fl_next)
		__locks_delete_block(waiter);
	else
		status = -ENOENT;
	spin_unlock(&blocked_lock_lock);
	return status;
}
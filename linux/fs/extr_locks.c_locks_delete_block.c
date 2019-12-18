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
struct file_lock {int /*<<< orphan*/ * fl_blocker; int /*<<< orphan*/  fl_blocked_requests; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __locks_delete_block (struct file_lock*) ; 
 int /*<<< orphan*/  __locks_wake_up_blocks (struct file_lock*) ; 
 int /*<<< orphan*/  blocked_lock_lock ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int locks_delete_block(struct file_lock *waiter)
{
	int status = -ENOENT;

	/*
	 * If fl_blocker is NULL, it won't be set again as this thread
	 * "owns" the lock and is the only one that might try to claim
	 * the lock.  So it is safe to test fl_blocker locklessly.
	 * Also if fl_blocker is NULL, this waiter is not listed on
	 * fl_blocked_requests for some lock, so no other request can
	 * be added to the list of fl_blocked_requests for this
	 * request.  So if fl_blocker is NULL, it is safe to
	 * locklessly check if fl_blocked_requests is empty.  If both
	 * of these checks succeed, there is no need to take the lock.
	 */
	if (waiter->fl_blocker == NULL &&
	    list_empty(&waiter->fl_blocked_requests))
		return status;
	spin_lock(&blocked_lock_lock);
	if (waiter->fl_blocker)
		status = 0;
	__locks_wake_up_blocks(waiter);
	__locks_delete_block(waiter);
	spin_unlock(&blocked_lock_lock);
	return status;
}
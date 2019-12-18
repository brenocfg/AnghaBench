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
struct file_lock {int /*<<< orphan*/  fl_blocked_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  __locks_wake_up_blocks (struct file_lock*) ; 
 int /*<<< orphan*/  blocked_lock_lock ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locks_wake_up_blocks(struct file_lock *blocker)
{
	/*
	 * Avoid taking global lock if list is empty. This is safe since new
	 * blocked requests are only added to the list under the flc_lock, and
	 * the flc_lock is always held here. Note that removal from the
	 * fl_blocked_requests list does not require the flc_lock, so we must
	 * recheck list_empty() after acquiring the blocked_lock_lock.
	 */
	if (list_empty(&blocker->fl_blocked_requests))
		return;

	spin_lock(&blocked_lock_lock);
	__locks_wake_up_blocks(blocker);
	spin_unlock(&blocked_lock_lock);
}
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
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __locks_insert_block (struct file_lock*,struct file_lock*,int (*) (struct file_lock*,struct file_lock*)) ; 
 int /*<<< orphan*/  blocked_lock_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void locks_insert_block(struct file_lock *blocker,
			       struct file_lock *waiter,
			       bool conflict(struct file_lock *,
					     struct file_lock *))
{
	spin_lock(&blocked_lock_lock);
	__locks_insert_block(blocker, waiter, conflict);
	spin_unlock(&blocked_lock_lock);
}
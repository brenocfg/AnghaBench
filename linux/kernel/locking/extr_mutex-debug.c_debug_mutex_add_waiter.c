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
struct task_struct {struct mutex_waiter* blocked_on; } ;
struct mutex_waiter {int dummy; } ;
struct mutex {int /*<<< orphan*/  wait_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void debug_mutex_add_waiter(struct mutex *lock, struct mutex_waiter *waiter,
			    struct task_struct *task)
{
	lockdep_assert_held(&lock->wait_lock);

	/* Mark the current thread as blocked on the lock: */
	task->blocked_on = waiter;
}
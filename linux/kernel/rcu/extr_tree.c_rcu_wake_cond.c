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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int RCU_KTHREAD_YIELDING ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ is_idle_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static void rcu_wake_cond(struct task_struct *t, int status)
{
	/*
	 * If the thread is yielding, only wake it when this
	 * is invoked from idle
	 */
	if (t && (status != RCU_KTHREAD_YIELDING || is_idle_task(current)))
		wake_up_process(t);
}
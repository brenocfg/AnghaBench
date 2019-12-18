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
struct rcuwait {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 struct task_struct* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

void rcuwait_wake_up(struct rcuwait *w)
{
	struct task_struct *task;

	rcu_read_lock();

	/*
	 * Order condition vs @task, such that everything prior to the load
	 * of @task is visible. This is the condition as to why the user called
	 * rcuwait_trywake() in the first place. Pairs with set_current_state()
	 * barrier (A) in rcuwait_wait_event().
	 *
	 *    WAIT                WAKE
	 *    [S] tsk = current	  [S] cond = true
	 *        MB (A)	      MB (B)
	 *    [L] cond		  [L] tsk
	 */
	smp_mb(); /* (B) */

	task = rcu_dereference(w->task);
	if (task)
		wake_up_process(task);
	rcu_read_unlock();
}
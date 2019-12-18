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
struct task_struct {scalar_t__ state; } ;

/* Variables and functions */
 unsigned long SOFTIRQ_NOW_MASK ; 
 scalar_t__ TASK_RUNNING ; 
 int /*<<< orphan*/  __kthread_should_park (struct task_struct*) ; 
 struct task_struct* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksoftirqd ; 

__attribute__((used)) static bool ksoftirqd_running(unsigned long pending)
{
	struct task_struct *tsk = __this_cpu_read(ksoftirqd);

	if (pending & SOFTIRQ_NOW_MASK)
		return false;
	return tsk && (tsk->state == TASK_RUNNING) &&
		!__kthread_should_park(tsk);
}
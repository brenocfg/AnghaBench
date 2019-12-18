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
 int /*<<< orphan*/  CONFIG_POSIX_TIMERS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_process_tick (struct task_struct*,int) ; 
 struct task_struct* current ; 
 scalar_t__ in_irq () ; 
 int /*<<< orphan*/  irq_work_tick () ; 
 int /*<<< orphan*/  rcu_sched_clock_irq (int) ; 
 int /*<<< orphan*/  run_local_timers () ; 
 int /*<<< orphan*/  run_posix_cpu_timers () ; 
 int /*<<< orphan*/  scheduler_tick () ; 

void update_process_times(int user_tick)
{
	struct task_struct *p = current;

	/* Note: this timer irq context must be accounted for as well. */
	account_process_tick(p, user_tick);
	run_local_timers();
	rcu_sched_clock_irq(user_tick);
#ifdef CONFIG_IRQ_WORK
	if (in_irq())
		irq_work_tick();
#endif
	scheduler_tick();
	if (IS_ENABLED(CONFIG_POSIX_TIMERS))
		run_posix_cpu_timers();
}
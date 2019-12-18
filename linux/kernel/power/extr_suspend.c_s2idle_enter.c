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

/* Variables and functions */
 int /*<<< orphan*/  PM_SUSPEND_TO_IDLE ; 
 scalar_t__ S2IDLE_STATE_ENTER ; 
 scalar_t__ S2IDLE_STATE_NONE ; 
 scalar_t__ S2IDLE_STATE_WAKE ; 
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  cpuidle_pause () ; 
 int /*<<< orphan*/  cpuidle_resume () ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 scalar_t__ pm_wakeup_pending () ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s2idle_lock ; 
 scalar_t__ s2idle_state ; 
 int /*<<< orphan*/  s2idle_wait_head ; 
 int /*<<< orphan*/  swait_event_exclusive (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_suspend_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_all_idle_cpus () ; 

__attribute__((used)) static void s2idle_enter(void)
{
	trace_suspend_resume(TPS("machine_suspend"), PM_SUSPEND_TO_IDLE, true);

	raw_spin_lock_irq(&s2idle_lock);
	if (pm_wakeup_pending())
		goto out;

	s2idle_state = S2IDLE_STATE_ENTER;
	raw_spin_unlock_irq(&s2idle_lock);

	get_online_cpus();
	cpuidle_resume();

	/* Push all the CPUs into the idle loop. */
	wake_up_all_idle_cpus();
	/* Make the current CPU wait so it can enter the idle loop too. */
	swait_event_exclusive(s2idle_wait_head,
		    s2idle_state == S2IDLE_STATE_WAKE);

	cpuidle_pause();
	put_online_cpus();

	raw_spin_lock_irq(&s2idle_lock);

 out:
	s2idle_state = S2IDLE_STATE_NONE;
	raw_spin_unlock_irq(&s2idle_lock);

	trace_suspend_resume(TPS("machine_suspend"), PM_SUSPEND_TO_IDLE, false);
}
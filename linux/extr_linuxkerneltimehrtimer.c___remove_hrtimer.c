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
typedef  int u8 ;
struct hrtimer_cpu_base {int active_bases; struct hrtimer* next_timer; } ;
struct hrtimer_clock_base {int index; int /*<<< orphan*/  active; struct hrtimer_cpu_base* cpu_base; } ;
struct hrtimer {int state; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int HRTIMER_STATE_ENQUEUED ; 
 int /*<<< orphan*/  hrtimer_force_reprogram (struct hrtimer_cpu_base*,int) ; 
 int /*<<< orphan*/  timerqueue_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __remove_hrtimer(struct hrtimer *timer,
			     struct hrtimer_clock_base *base,
			     u8 newstate, int reprogram)
{
	struct hrtimer_cpu_base *cpu_base = base->cpu_base;
	u8 state = timer->state;

	timer->state = newstate;
	if (!(state & HRTIMER_STATE_ENQUEUED))
		return;

	if (!timerqueue_del(&base->active, &timer->node))
		cpu_base->active_bases &= ~(1 << base->index);

	/*
	 * Note: If reprogram is false we do not update
	 * cpu_base->next_timer. This happens when we remove the first
	 * timer on a remote cpu. No harm as we never dereference
	 * cpu_base->next_timer. So the worst thing what can happen is
	 * an superflous call to hrtimer_force_reprogram() on the
	 * remote cpu later on if the same timer gets enqueued again.
	 */
	if (reprogram && timer == cpu_base->next_timer)
		hrtimer_force_reprogram(cpu_base, 1);
}
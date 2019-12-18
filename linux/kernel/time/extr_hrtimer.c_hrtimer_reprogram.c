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
struct hrtimer_cpu_base {scalar_t__ softirq_expires_next; scalar_t__ expires_next; scalar_t__ hang_detected; struct hrtimer* next_timer; scalar_t__ in_hrtirq; struct hrtimer* softirq_next_timer; scalar_t__ softirq_activated; } ;
struct hrtimer_clock_base {struct hrtimer_cpu_base* cpu_base; int /*<<< orphan*/  offset; } ;
struct hrtimer {scalar_t__ is_soft; struct hrtimer_clock_base* base; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __hrtimer_hres_active (struct hrtimer_cpu_base*) ; 
 int /*<<< orphan*/  hrtimer_bases ; 
 int /*<<< orphan*/  hrtimer_get_expires (struct hrtimer*) ; 
 scalar_t__ hrtimer_get_expires_tv64 (struct hrtimer*) ; 
 int /*<<< orphan*/  ktime_before (scalar_t__,scalar_t__) ; 
 scalar_t__ ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hrtimer_cpu_base* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_program_event (scalar_t__,int) ; 

__attribute__((used)) static void hrtimer_reprogram(struct hrtimer *timer, bool reprogram)
{
	struct hrtimer_cpu_base *cpu_base = this_cpu_ptr(&hrtimer_bases);
	struct hrtimer_clock_base *base = timer->base;
	ktime_t expires = ktime_sub(hrtimer_get_expires(timer), base->offset);

	WARN_ON_ONCE(hrtimer_get_expires_tv64(timer) < 0);

	/*
	 * CLOCK_REALTIME timer might be requested with an absolute
	 * expiry time which is less than base->offset. Set it to 0.
	 */
	if (expires < 0)
		expires = 0;

	if (timer->is_soft) {
		/*
		 * soft hrtimer could be started on a remote CPU. In this
		 * case softirq_expires_next needs to be updated on the
		 * remote CPU. The soft hrtimer will not expire before the
		 * first hard hrtimer on the remote CPU -
		 * hrtimer_check_target() prevents this case.
		 */
		struct hrtimer_cpu_base *timer_cpu_base = base->cpu_base;

		if (timer_cpu_base->softirq_activated)
			return;

		if (!ktime_before(expires, timer_cpu_base->softirq_expires_next))
			return;

		timer_cpu_base->softirq_next_timer = timer;
		timer_cpu_base->softirq_expires_next = expires;

		if (!ktime_before(expires, timer_cpu_base->expires_next) ||
		    !reprogram)
			return;
	}

	/*
	 * If the timer is not on the current cpu, we cannot reprogram
	 * the other cpus clock event device.
	 */
	if (base->cpu_base != cpu_base)
		return;

	/*
	 * If the hrtimer interrupt is running, then it will
	 * reevaluate the clock bases and reprogram the clock event
	 * device. The callbacks are always executed in hard interrupt
	 * context so we don't need an extra check for a running
	 * callback.
	 */
	if (cpu_base->in_hrtirq)
		return;

	if (expires >= cpu_base->expires_next)
		return;

	/* Update the pointer to the next expiring timer */
	cpu_base->next_timer = timer;
	cpu_base->expires_next = expires;

	/*
	 * If hres is not active, hardware does not have to be
	 * programmed yet.
	 *
	 * If a hang was detected in the last timer interrupt then we
	 * do not schedule a timer which is earlier than the expiry
	 * which we enforced in the hang detection. We want the system
	 * to make progress.
	 */
	if (!__hrtimer_hres_active(cpu_base) || cpu_base->hang_detected)
		return;

	/*
	 * Program the timer hardware. We enforce the expiry for
	 * events which are already in the past.
	 */
	tick_program_event(expires, 1);
}
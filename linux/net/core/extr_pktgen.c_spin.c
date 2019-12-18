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
struct pktgen_dev {int /*<<< orphan*/  delay; int /*<<< orphan*/  next_tx; int /*<<< orphan*/  idle_acc; scalar_t__ running; } ;
struct hrtimer_sleeper {int /*<<< orphan*/  timer; scalar_t__ task; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  destroy_hrtimer_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_expires_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_init_sleeper_on_stack (struct hrtimer_sleeper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_set_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_sleeper_start_expires (struct hrtimer_sleeper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spin(struct pktgen_dev *pkt_dev, ktime_t spin_until)
{
	ktime_t start_time, end_time;
	s64 remaining;
	struct hrtimer_sleeper t;

	hrtimer_init_sleeper_on_stack(&t, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	hrtimer_set_expires(&t.timer, spin_until);

	remaining = ktime_to_ns(hrtimer_expires_remaining(&t.timer));
	if (remaining <= 0)
		goto out;

	start_time = ktime_get();
	if (remaining < 100000) {
		/* for small delays (<100us), just loop until limit is reached */
		do {
			end_time = ktime_get();
		} while (ktime_compare(end_time, spin_until) < 0);
	} else {
		do {
			set_current_state(TASK_INTERRUPTIBLE);
			hrtimer_sleeper_start_expires(&t, HRTIMER_MODE_ABS);

			if (likely(t.task))
				schedule();

			hrtimer_cancel(&t.timer);
		} while (t.task && pkt_dev->running && !signal_pending(current));
		__set_current_state(TASK_RUNNING);
		end_time = ktime_get();
	}

	pkt_dev->idle_acc += ktime_to_ns(ktime_sub(end_time, start_time));
out:
	pkt_dev->next_tx = ktime_add_ns(spin_until, pkt_dev->delay);
	destroy_hrtimer_on_stack(&t.timer);
}
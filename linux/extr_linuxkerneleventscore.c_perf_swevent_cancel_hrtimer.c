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
struct hw_perf_event {int /*<<< orphan*/  hrtimer; int /*<<< orphan*/  period_left; } ;
struct perf_event {struct hw_perf_event hw; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_get_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_swevent_cancel_hrtimer(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	if (is_sampling_event(event)) {
		ktime_t remaining = hrtimer_get_remaining(&hwc->hrtimer);
		local64_set(&hwc->period_left, ktime_to_ns(remaining));

		hrtimer_cancel(&hwc->hrtimer);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ freq; } ;
struct hw_perf_event {scalar_t__ interrupts_seq; int interrupts; scalar_t__ freq_time_stamp; int /*<<< orphan*/  last_period; } ;
struct perf_event {TYPE_1__ attr; struct hw_perf_event hw; } ;
typedef  int s64 ;

/* Variables and functions */
 int MAX_INTERRUPTS ; 
 int /*<<< orphan*/  TICK_DEP_BIT_PERF_EVENTS ; 
 int TICK_NSEC ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int max_samples_per_tick ; 
 int /*<<< orphan*/  perf_adjust_period (struct perf_event*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ perf_clock () ; 
 int /*<<< orphan*/  perf_log_throttle (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_throttled_count ; 
 int /*<<< orphan*/  perf_throttled_seq ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  tick_dep_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
__perf_event_account_interrupt(struct perf_event *event, int throttle)
{
	struct hw_perf_event *hwc = &event->hw;
	int ret = 0;
	u64 seq;

	seq = __this_cpu_read(perf_throttled_seq);
	if (seq != hwc->interrupts_seq) {
		hwc->interrupts_seq = seq;
		hwc->interrupts = 1;
	} else {
		hwc->interrupts++;
		if (unlikely(throttle
			     && hwc->interrupts >= max_samples_per_tick)) {
			__this_cpu_inc(perf_throttled_count);
			tick_dep_set_cpu(smp_processor_id(), TICK_DEP_BIT_PERF_EVENTS);
			hwc->interrupts = MAX_INTERRUPTS;
			perf_log_throttle(event, 0);
			ret = 1;
		}
	}

	if (event->attr.freq) {
		u64 now = perf_clock();
		s64 delta = now - hwc->freq_time_stamp;

		hwc->freq_time_stamp = now;

		if (delta > 0 && delta < 2*TICK_NSEC)
			perf_adjust_period(event, delta, hwc->last_period, true);
	}

	return ret;
}
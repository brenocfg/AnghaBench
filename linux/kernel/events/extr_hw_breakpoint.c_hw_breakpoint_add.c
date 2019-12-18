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
struct TYPE_2__ {int /*<<< orphan*/  sample_period; int /*<<< orphan*/  last_period; int /*<<< orphan*/  state; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int PERF_EF_START ; 
 int /*<<< orphan*/  PERF_HES_STOPPED ; 
 int arch_install_hw_breakpoint (struct perf_event*) ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 int /*<<< orphan*/  perf_swevent_set_period (struct perf_event*) ; 

__attribute__((used)) static int hw_breakpoint_add(struct perf_event *bp, int flags)
{
	if (!(flags & PERF_EF_START))
		bp->hw.state = PERF_HES_STOPPED;

	if (is_sampling_event(bp)) {
		bp->hw.last_period = bp->hw.sample_period;
		perf_swevent_set_period(bp);
	}

	return arch_install_hw_breakpoint(bp);
}
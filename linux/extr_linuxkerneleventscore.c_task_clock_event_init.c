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
struct TYPE_2__ {scalar_t__ type; scalar_t__ config; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 scalar_t__ PERF_COUNT_SW_TASK_CLOCK ; 
 scalar_t__ PERF_TYPE_SOFTWARE ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int /*<<< orphan*/  perf_swevent_init_hrtimer (struct perf_event*) ; 

__attribute__((used)) static int task_clock_event_init(struct perf_event *event)
{
	if (event->attr.type != PERF_TYPE_SOFTWARE)
		return -ENOENT;

	if (event->attr.config != PERF_COUNT_SW_TASK_CLOCK)
		return -ENOENT;

	/*
	 * no branch sampling for software events
	 */
	if (has_branch_stack(event))
		return -EOPNOTSUPP;

	perf_swevent_init_hrtimer(event);

	return 0;
}
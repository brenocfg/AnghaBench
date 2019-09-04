#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; } ;
struct perf_event {scalar_t__ state; TYPE_2__* pmu; TYPE_1__ hw; } ;
struct TYPE_4__ {int (* event_idx ) (struct perf_event*) ;} ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 int PERF_HES_STOPPED ; 
 int stub1 (struct perf_event*) ; 

__attribute__((used)) static int perf_event_index(struct perf_event *event)
{
	if (event->hw.state & PERF_HES_STOPPED)
		return 0;

	if (event->state != PERF_EVENT_STATE_ACTIVE)
		return 0;

	return event->pmu->event_idx(event);
}
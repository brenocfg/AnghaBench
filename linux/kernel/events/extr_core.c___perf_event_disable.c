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
struct perf_event_context {int is_active; } ;
struct perf_event {scalar_t__ state; struct perf_event* group_leader; } ;
struct perf_cpu_context {int dummy; } ;

/* Variables and functions */
 int EVENT_TIME ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 int /*<<< orphan*/  PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  event_sched_out (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  group_sched_out (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_event_set_state (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cgrp_time_from_event (struct perf_event*) ; 
 int /*<<< orphan*/  update_context_time (struct perf_event_context*) ; 

__attribute__((used)) static void __perf_event_disable(struct perf_event *event,
				 struct perf_cpu_context *cpuctx,
				 struct perf_event_context *ctx,
				 void *info)
{
	if (event->state < PERF_EVENT_STATE_INACTIVE)
		return;

	if (ctx->is_active & EVENT_TIME) {
		update_context_time(ctx);
		update_cgrp_time_from_event(event);
	}

	if (event == event->group_leader)
		group_sched_out(event, cpuctx, ctx);
	else
		event_sched_out(event, cpuctx, ctx);

	perf_event_set_state(event, PERF_EVENT_STATE_OFF);
}
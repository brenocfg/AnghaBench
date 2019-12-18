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
struct perf_event_context {scalar_t__ task; scalar_t__ is_active; } ;
struct perf_event {scalar_t__ state; struct perf_event* group_leader; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TIME ; 
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 scalar_t__ PERF_EVENT_STATE_ERROR ; 
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ctx_resched (struct perf_cpu_context*,struct perf_event_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_sched_in (struct perf_event_context*,struct perf_cpu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_sched_out (struct perf_event_context*,struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  event_filter_match (struct perf_event*) ; 
 int /*<<< orphan*/  get_event_type (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_set_state (struct perf_event*,scalar_t__) ; 

__attribute__((used)) static void __perf_event_enable(struct perf_event *event,
				struct perf_cpu_context *cpuctx,
				struct perf_event_context *ctx,
				void *info)
{
	struct perf_event *leader = event->group_leader;
	struct perf_event_context *task_ctx;

	if (event->state >= PERF_EVENT_STATE_INACTIVE ||
	    event->state <= PERF_EVENT_STATE_ERROR)
		return;

	if (ctx->is_active)
		ctx_sched_out(ctx, cpuctx, EVENT_TIME);

	perf_event_set_state(event, PERF_EVENT_STATE_INACTIVE);

	if (!ctx->is_active)
		return;

	if (!event_filter_match(event)) {
		ctx_sched_in(ctx, cpuctx, EVENT_TIME, current);
		return;
	}

	/*
	 * If the event is in a group and isn't the group leader,
	 * then don't put it on unless the group is on.
	 */
	if (leader != event && leader->state != PERF_EVENT_STATE_ACTIVE) {
		ctx_sched_in(ctx, cpuctx, EVENT_TIME, current);
		return;
	}

	task_ctx = cpuctx->task_ctx;
	if (ctx->task)
		WARN_ON_ONCE(task_ctx != ctx);

	ctx_resched(cpuctx, task_ctx, get_event_type(event));
}
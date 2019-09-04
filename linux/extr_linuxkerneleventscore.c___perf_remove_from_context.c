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
struct perf_event_context {int is_active; scalar_t__ task; int /*<<< orphan*/  nr_events; } ;
struct perf_event {int dummy; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;

/* Variables and functions */
 unsigned long DETACH_GROUP ; 
 int EVENT_TIME ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  event_sched_out (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  list_del_event (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_group_detach (struct perf_event*) ; 
 int /*<<< orphan*/  update_cgrp_time_from_cpuctx (struct perf_cpu_context*) ; 
 int /*<<< orphan*/  update_context_time (struct perf_event_context*) ; 

__attribute__((used)) static void
__perf_remove_from_context(struct perf_event *event,
			   struct perf_cpu_context *cpuctx,
			   struct perf_event_context *ctx,
			   void *info)
{
	unsigned long flags = (unsigned long)info;

	if (ctx->is_active & EVENT_TIME) {
		update_context_time(ctx);
		update_cgrp_time_from_cpuctx(cpuctx);
	}

	event_sched_out(event, cpuctx, ctx);
	if (flags & DETACH_GROUP)
		perf_group_detach(event);
	list_del_event(event, ctx);

	if (!ctx->nr_events && ctx->is_active) {
		ctx->is_active = 0;
		if (ctx->task) {
			WARN_ON_ONCE(cpuctx->task_ctx != ctx);
			cpuctx->task_ctx = NULL;
		}
	}
}
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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int dummy; } ;
struct perf_event_context {int is_active; int /*<<< orphan*/  timestamp; scalar_t__ task; int /*<<< orphan*/  nr_events; int /*<<< orphan*/  lock; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;
typedef  enum event_type_t { ____Placeholder_event_type_t } event_type_t ;

/* Variables and functions */
 int EVENT_FLEXIBLE ; 
 int EVENT_PINNED ; 
 int EVENT_TIME ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ctx_flexible_sched_in (struct perf_event_context*,struct perf_cpu_context*) ; 
 int /*<<< orphan*/  ctx_pinned_sched_in (struct perf_event_context*,struct perf_cpu_context*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_cgroup_set_timestamp (struct task_struct*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_clock () ; 

__attribute__((used)) static void
ctx_sched_in(struct perf_event_context *ctx,
	     struct perf_cpu_context *cpuctx,
	     enum event_type_t event_type,
	     struct task_struct *task)
{
	int is_active = ctx->is_active;
	u64 now;

	lockdep_assert_held(&ctx->lock);

	if (likely(!ctx->nr_events))
		return;

	ctx->is_active |= (event_type | EVENT_TIME);
	if (ctx->task) {
		if (!is_active)
			cpuctx->task_ctx = ctx;
		else
			WARN_ON_ONCE(cpuctx->task_ctx != ctx);
	}

	is_active ^= ctx->is_active; /* changed bits */

	if (is_active & EVENT_TIME) {
		/* start ctx time */
		now = perf_clock();
		ctx->timestamp = now;
		perf_cgroup_set_timestamp(task, ctx);
	}

	/*
	 * First go through the list and put on any pinned groups
	 * in order to give them the best chance of going on.
	 */
	if (is_active & EVENT_PINNED)
		ctx_pinned_sched_in(ctx, cpuctx);

	/* Then walk through the lower prio flexible groups */
	if (is_active & EVENT_FLEXIBLE)
		ctx_flexible_sched_in(ctx, cpuctx);
}
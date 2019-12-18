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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tree; } ;
struct perf_event_context {int /*<<< orphan*/  pmu; TYPE_1__ pinned_groups; int /*<<< orphan*/  nr_events; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_FLEXIBLE ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 int /*<<< orphan*/  cpu_ctx_sched_out (struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_ctx_lock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_ctx_unlock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_event_sched_in (struct perf_cpu_context*,struct perf_event_context*,struct task_struct*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_event_context_sched_in(struct perf_event_context *ctx,
					struct task_struct *task)
{
	struct perf_cpu_context *cpuctx;

	cpuctx = __get_cpu_context(ctx);
	if (cpuctx->task_ctx == ctx)
		return;

	perf_ctx_lock(cpuctx, ctx);
	/*
	 * We must check ctx->nr_events while holding ctx->lock, such
	 * that we serialize against perf_install_in_context().
	 */
	if (!ctx->nr_events)
		goto unlock;

	perf_pmu_disable(ctx->pmu);
	/*
	 * We want to keep the following priority order:
	 * cpu pinned (that don't need to move), task pinned,
	 * cpu flexible, task flexible.
	 *
	 * However, if task's ctx is not carrying any pinned
	 * events, no need to flip the cpuctx's events around.
	 */
	if (!RB_EMPTY_ROOT(&ctx->pinned_groups.tree))
		cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);
	perf_event_sched_in(cpuctx, ctx, task);
	perf_pmu_enable(ctx->pmu);

unlock:
	perf_ctx_unlock(cpuctx, ctx);
}
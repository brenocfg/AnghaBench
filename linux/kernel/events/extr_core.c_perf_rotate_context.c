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
struct perf_event_context {int rotate_necessary; int /*<<< orphan*/  pmu; } ;
struct perf_event {int dummy; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; struct perf_event_context ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_FLEXIBLE ; 
 int /*<<< orphan*/  cpu_ctx_sched_out (struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 struct perf_event* ctx_event_to_rotate (struct perf_event_context*) ; 
 int /*<<< orphan*/  ctx_sched_out (struct perf_event_context*,struct perf_cpu_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  perf_ctx_lock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_ctx_unlock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_event_sched_in (struct perf_cpu_context*,struct perf_event_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotate_ctx (struct perf_event_context*,struct perf_event*) ; 

__attribute__((used)) static bool perf_rotate_context(struct perf_cpu_context *cpuctx)
{
	struct perf_event *cpu_event = NULL, *task_event = NULL;
	struct perf_event_context *task_ctx = NULL;
	int cpu_rotate, task_rotate;

	/*
	 * Since we run this from IRQ context, nobody can install new
	 * events, thus the event count values are stable.
	 */

	cpu_rotate = cpuctx->ctx.rotate_necessary;
	task_ctx = cpuctx->task_ctx;
	task_rotate = task_ctx ? task_ctx->rotate_necessary : 0;

	if (!(cpu_rotate || task_rotate))
		return false;

	perf_ctx_lock(cpuctx, cpuctx->task_ctx);
	perf_pmu_disable(cpuctx->ctx.pmu);

	if (task_rotate)
		task_event = ctx_event_to_rotate(task_ctx);
	if (cpu_rotate)
		cpu_event = ctx_event_to_rotate(&cpuctx->ctx);

	/*
	 * As per the order given at ctx_resched() first 'pop' task flexible
	 * and then, if needed CPU flexible.
	 */
	if (task_event || (task_ctx && cpu_event))
		ctx_sched_out(task_ctx, cpuctx, EVENT_FLEXIBLE);
	if (cpu_event)
		cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);

	if (task_event)
		rotate_ctx(task_ctx, task_event);
	if (cpu_event)
		rotate_ctx(&cpuctx->ctx, cpu_event);

	perf_event_sched_in(cpuctx, task_ctx, current);

	perf_pmu_enable(cpuctx->ctx.pmu);
	perf_ctx_unlock(cpuctx, cpuctx->task_ctx);

	return true;
}
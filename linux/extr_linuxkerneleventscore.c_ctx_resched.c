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
struct perf_event_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu; } ;
struct perf_cpu_context {TYPE_1__ ctx; } ;
typedef  enum event_type_t { ____Placeholder_event_type_t } event_type_t ;

/* Variables and functions */
 int EVENT_ALL ; 
 int EVENT_CPU ; 
 int EVENT_FLEXIBLE ; 
 int EVENT_PINNED ; 
 int /*<<< orphan*/  cpu_ctx_sched_out (struct perf_cpu_context*,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  perf_event_sched_in (struct perf_cpu_context*,struct perf_event_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_ctx_sched_out (struct perf_cpu_context*,struct perf_event_context*,int) ; 

__attribute__((used)) static void ctx_resched(struct perf_cpu_context *cpuctx,
			struct perf_event_context *task_ctx,
			enum event_type_t event_type)
{
	enum event_type_t ctx_event_type;
	bool cpu_event = !!(event_type & EVENT_CPU);

	/*
	 * If pinned groups are involved, flexible groups also need to be
	 * scheduled out.
	 */
	if (event_type & EVENT_PINNED)
		event_type |= EVENT_FLEXIBLE;

	ctx_event_type = event_type & EVENT_ALL;

	perf_pmu_disable(cpuctx->ctx.pmu);
	if (task_ctx)
		task_ctx_sched_out(cpuctx, task_ctx, event_type);

	/*
	 * Decide which cpu ctx groups to schedule out based on the types
	 * of events that caused rescheduling:
	 *  - EVENT_CPU: schedule out corresponding groups;
	 *  - EVENT_PINNED task events: schedule out EVENT_FLEXIBLE groups;
	 *  - otherwise, do nothing more.
	 */
	if (cpu_event)
		cpu_ctx_sched_out(cpuctx, ctx_event_type);
	else if (ctx_event_type & EVENT_PINNED)
		cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);

	perf_event_sched_in(cpuctx, task_ctx, current);
	perf_pmu_enable(cpuctx->ctx.pmu);
}
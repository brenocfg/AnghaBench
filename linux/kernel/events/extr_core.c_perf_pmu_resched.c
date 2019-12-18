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
struct pmu {int /*<<< orphan*/  pmu_cpu_context; } ;
struct perf_event_context {int dummy; } ;
struct perf_cpu_context {struct perf_event_context* task_ctx; } ;

/* Variables and functions */
 int EVENT_ALL ; 
 int EVENT_CPU ; 
 int /*<<< orphan*/  ctx_resched (struct perf_cpu_context*,struct perf_event_context*,int) ; 
 int /*<<< orphan*/  perf_ctx_lock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_ctx_unlock (struct perf_cpu_context*,struct perf_event_context*) ; 
 struct perf_cpu_context* this_cpu_ptr (int /*<<< orphan*/ ) ; 

void perf_pmu_resched(struct pmu *pmu)
{
	struct perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);
	struct perf_event_context *task_ctx = cpuctx->task_ctx;

	perf_ctx_lock(cpuctx, task_ctx);
	ctx_resched(cpuctx, task_ctx, EVENT_ALL|EVENT_CPU);
	perf_ctx_unlock(cpuctx, task_ctx);
}
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
struct remote_output {int err; int /*<<< orphan*/  rb; } ;
struct pmu {int /*<<< orphan*/  pmu_cpu_context; } ;
struct perf_event {int /*<<< orphan*/  rb; TYPE_1__* ctx; } ;
struct perf_cpu_context {int /*<<< orphan*/ * task_ctx; int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {struct pmu* pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event_output_stop ; 
 int /*<<< orphan*/  perf_iterate_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct remote_output*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct perf_cpu_context* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __perf_pmu_output_stop(void *info)
{
	struct perf_event *event = info;
	struct pmu *pmu = event->ctx->pmu;
	struct perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);
	struct remote_output ro = {
		.rb	= event->rb,
	};

	rcu_read_lock();
	perf_iterate_ctx(&cpuctx->ctx, __perf_event_output_stop, &ro, false);
	if (cpuctx->task_ctx)
		perf_iterate_ctx(cpuctx->task_ctx, __perf_event_output_stop,
				   &ro, false);
	rcu_read_unlock();

	return ro.err;
}
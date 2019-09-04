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
struct task_struct {int dummy; } ;
struct perf_event_context {int dummy; } ;
struct perf_cpu_context {struct perf_event_context ctx; } ;
typedef  enum event_type_t { ____Placeholder_event_type_t } event_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctx_sched_in (struct perf_event_context*,struct perf_cpu_context*,int,struct task_struct*) ; 

__attribute__((used)) static void cpu_ctx_sched_in(struct perf_cpu_context *cpuctx,
			     enum event_type_t event_type,
			     struct task_struct *task)
{
	struct perf_event_context *ctx = &cpuctx->ctx;

	ctx_sched_in(ctx, cpuctx, event_type, task);
}
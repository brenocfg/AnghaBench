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
struct perf_cpu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_FLEXIBLE ; 
 int /*<<< orphan*/  EVENT_PINNED ; 
 int /*<<< orphan*/  cpu_ctx_sched_in (struct perf_cpu_context*,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  ctx_sched_in (struct perf_event_context*,struct perf_cpu_context*,int /*<<< orphan*/ ,struct task_struct*) ; 

__attribute__((used)) static void perf_event_sched_in(struct perf_cpu_context *cpuctx,
				struct perf_event_context *ctx,
				struct task_struct *task)
{
	cpu_ctx_sched_in(cpuctx, EVENT_PINNED, task);
	if (ctx)
		ctx_sched_in(ctx, cpuctx, EVENT_PINNED, task);
	cpu_ctx_sched_in(cpuctx, EVENT_FLEXIBLE, task);
	if (ctx)
		ctx_sched_in(ctx, cpuctx, EVENT_FLEXIBLE, task);
}
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
struct perf_event_context {scalar_t__ task; int /*<<< orphan*/  is_active; } ;
struct perf_event {struct perf_event_context* ctx; } ;
struct perf_cpu_context {struct perf_event_context ctx; struct perf_event_context* task_ctx; } ;
struct event_function_struct {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*,int /*<<< orphan*/ ) ;struct perf_event* event; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  perf_ctx_lock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_ctx_unlock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_function(void *info)
{
	struct event_function_struct *efs = info;
	struct perf_event *event = efs->event;
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	struct perf_event_context *task_ctx = cpuctx->task_ctx;
	int ret = 0;

	lockdep_assert_irqs_disabled();

	perf_ctx_lock(cpuctx, task_ctx);
	/*
	 * Since we do the IPI call without holding ctx->lock things can have
	 * changed, double check we hit the task we set out to hit.
	 */
	if (ctx->task) {
		if (ctx->task != current) {
			ret = -ESRCH;
			goto unlock;
		}

		/*
		 * We only use event_function_call() on established contexts,
		 * and event_function() is only ever called when active (or
		 * rather, we'll have bailed in task_function_call() or the
		 * above ctx->task != current test), therefore we must have
		 * ctx->is_active here.
		 */
		WARN_ON_ONCE(!ctx->is_active);
		/*
		 * And since we have ctx->is_active, cpuctx->task_ctx must
		 * match.
		 */
		WARN_ON_ONCE(task_ctx != ctx);
	} else {
		WARN_ON_ONCE(&cpuctx->ctx != ctx);
	}

	efs->func(event, cpuctx, ctx, efs->data);
unlock:
	perf_ctx_unlock(cpuctx, task_ctx);

	return ret;
}
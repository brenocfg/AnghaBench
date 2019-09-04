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
struct perf_event_context {scalar_t__ is_active; struct task_struct* task; } ;
struct perf_event {struct perf_event_context* ctx; } ;
struct perf_cpu_context {struct perf_event_context ctx; struct perf_event_context* task_ctx; } ;
typedef  int /*<<< orphan*/  (* event_f ) (struct perf_event*,struct perf_cpu_context*,struct perf_event_context*,void*) ;

/* Variables and functions */
 struct task_struct* READ_ONCE (struct task_struct*) ; 
 struct task_struct* TASK_TOMBSTONE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct perf_cpu_context* __get_cpu_context (struct perf_event_context*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  perf_ctx_lock (struct perf_cpu_context*,struct perf_event_context*) ; 
 int /*<<< orphan*/  perf_ctx_unlock (struct perf_cpu_context*,struct perf_event_context*) ; 

__attribute__((used)) static void event_function_local(struct perf_event *event, event_f func, void *data)
{
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	struct task_struct *task = READ_ONCE(ctx->task);
	struct perf_event_context *task_ctx = NULL;

	lockdep_assert_irqs_disabled();

	if (task) {
		if (task == TASK_TOMBSTONE)
			return;

		task_ctx = ctx;
	}

	perf_ctx_lock(cpuctx, task_ctx);

	task = ctx->task;
	if (task == TASK_TOMBSTONE)
		goto unlock;

	if (task) {
		/*
		 * We must be either inactive or active and the right task,
		 * otherwise we're screwed, since we cannot IPI to somewhere
		 * else.
		 */
		if (ctx->is_active) {
			if (WARN_ON_ONCE(task != current))
				goto unlock;

			if (WARN_ON_ONCE(cpuctx->task_ctx != ctx))
				goto unlock;
		}
	} else {
		WARN_ON_ONCE(&cpuctx->ctx != ctx);
	}

	func(event, cpuctx, ctx, data);
unlock:
	perf_ctx_unlock(cpuctx, task_ctx);
}
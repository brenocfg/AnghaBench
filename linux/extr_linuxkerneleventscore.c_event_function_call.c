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
struct perf_event_context {int /*<<< orphan*/  lock; scalar_t__ is_active; struct task_struct* task; int /*<<< orphan*/  mutex; } ;
struct perf_event {int /*<<< orphan*/  cpu; int /*<<< orphan*/  parent; struct perf_event_context* ctx; } ;
struct event_function_struct {void* data; int /*<<< orphan*/  (* func ) (struct perf_event*,int /*<<< orphan*/ *,struct perf_event_context*,void*) ;struct perf_event* event; } ;
typedef  int /*<<< orphan*/  (* event_f ) (struct perf_event*,int /*<<< orphan*/ *,struct perf_event_context*,void*) ;

/* Variables and functions */
 struct task_struct* READ_ONCE (struct task_struct*) ; 
 struct task_struct* TASK_TOMBSTONE ; 
 int /*<<< orphan*/  cpu_function_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event_function_struct*) ; 
 int /*<<< orphan*/  event_function ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_function_call (struct task_struct*,int /*<<< orphan*/ ,struct event_function_struct*) ; 

__attribute__((used)) static void event_function_call(struct perf_event *event, event_f func, void *data)
{
	struct perf_event_context *ctx = event->ctx;
	struct task_struct *task = READ_ONCE(ctx->task); /* verified in event_function */
	struct event_function_struct efs = {
		.event = event,
		.func = func,
		.data = data,
	};

	if (!event->parent) {
		/*
		 * If this is a !child event, we must hold ctx::mutex to
		 * stabilize the the event->ctx relation. See
		 * perf_event_ctx_lock().
		 */
		lockdep_assert_held(&ctx->mutex);
	}

	if (!task) {
		cpu_function_call(event->cpu, event_function, &efs);
		return;
	}

	if (task == TASK_TOMBSTONE)
		return;

again:
	if (!task_function_call(task, event_function, &efs))
		return;

	raw_spin_lock_irq(&ctx->lock);
	/*
	 * Reload the task pointer, it might have been changed by
	 * a concurrent perf_event_context_sched_out().
	 */
	task = ctx->task;
	if (task == TASK_TOMBSTONE) {
		raw_spin_unlock_irq(&ctx->lock);
		return;
	}
	if (ctx->is_active) {
		raw_spin_unlock_irq(&ctx->lock);
		goto again;
	}
	func(event, NULL, ctx, data);
	raw_spin_unlock_irq(&ctx->lock);
}
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
struct perf_event_context {int /*<<< orphan*/  lock; struct task_struct* task; int /*<<< orphan*/  mutex; } ;
struct perf_event {int cpu; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 struct task_struct* READ_ONCE (struct task_struct*) ; 
 struct task_struct* TASK_TOMBSTONE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __perf_install_in_context ; 
 int /*<<< orphan*/  add_event_to_ctx (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  cpu_function_call (int,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  exclusive_event_installable (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,struct perf_event_context*) ; 
 scalar_t__ task_curr (struct task_struct*) ; 
 int /*<<< orphan*/  task_function_call (struct task_struct*,int /*<<< orphan*/ ,struct perf_event*) ; 

__attribute__((used)) static void
perf_install_in_context(struct perf_event_context *ctx,
			struct perf_event *event,
			int cpu)
{
	struct task_struct *task = READ_ONCE(ctx->task);

	lockdep_assert_held(&ctx->mutex);

	WARN_ON_ONCE(!exclusive_event_installable(event, ctx));

	if (event->cpu != -1)
		event->cpu = cpu;

	/*
	 * Ensures that if we can observe event->ctx, both the event and ctx
	 * will be 'complete'. See perf_iterate_sb_cpu().
	 */
	smp_store_release(&event->ctx, ctx);

	if (!task) {
		cpu_function_call(cpu, __perf_install_in_context, event);
		return;
	}

	/*
	 * Should not happen, we validate the ctx is still alive before calling.
	 */
	if (WARN_ON_ONCE(task == TASK_TOMBSTONE))
		return;

	/*
	 * Installing events is tricky because we cannot rely on ctx->is_active
	 * to be set in case this is the nr_events 0 -> 1 transition.
	 *
	 * Instead we use task_curr(), which tells us if the task is running.
	 * However, since we use task_curr() outside of rq::lock, we can race
	 * against the actual state. This means the result can be wrong.
	 *
	 * If we get a false positive, we retry, this is harmless.
	 *
	 * If we get a false negative, things are complicated. If we are after
	 * perf_event_context_sched_in() ctx::lock will serialize us, and the
	 * value must be correct. If we're before, it doesn't matter since
	 * perf_event_context_sched_in() will program the counter.
	 *
	 * However, this hinges on the remote context switch having observed
	 * our task->perf_event_ctxp[] store, such that it will in fact take
	 * ctx::lock in perf_event_context_sched_in().
	 *
	 * We do this by task_function_call(), if the IPI fails to hit the task
	 * we know any future context switch of task must see the
	 * perf_event_ctpx[] store.
	 */

	/*
	 * This smp_mb() orders the task->perf_event_ctxp[] store with the
	 * task_cpu() load, such that if the IPI then does not find the task
	 * running, a future context switch of that task must observe the
	 * store.
	 */
	smp_mb();
again:
	if (!task_function_call(task, __perf_install_in_context, event))
		return;

	raw_spin_lock_irq(&ctx->lock);
	task = ctx->task;
	if (WARN_ON_ONCE(task == TASK_TOMBSTONE)) {
		/*
		 * Cannot happen because we already checked above (which also
		 * cannot happen), and we hold ctx->mutex, which serializes us
		 * against perf_event_exit_task_context().
		 */
		raw_spin_unlock_irq(&ctx->lock);
		return;
	}
	/*
	 * If the task is not running, ctx->lock will avoid it becoming so,
	 * thus we can safely install the event.
	 */
	if (task_curr(task)) {
		raw_spin_unlock_irq(&ctx->lock);
		goto again;
	}
	add_event_to_ctx(event, ctx);
	raw_spin_unlock_irq(&ctx->lock);
}
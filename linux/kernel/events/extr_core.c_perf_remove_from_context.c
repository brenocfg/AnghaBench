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
struct perf_event_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; } ;
struct perf_event {int attach_state; struct perf_event_context* ctx; } ;

/* Variables and functions */
 unsigned long DETACH_GROUP ; 
 int PERF_ATTACH_CONTEXT ; 
 int PERF_ATTACH_GROUP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __perf_remove_from_context ; 
 int /*<<< orphan*/  event_function_call (struct perf_event*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_group_detach (struct perf_event*) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_remove_from_context(struct perf_event *event, unsigned long flags)
{
	struct perf_event_context *ctx = event->ctx;

	lockdep_assert_held(&ctx->mutex);

	event_function_call(event, __perf_remove_from_context, (void *)flags);

	/*
	 * The above event_function_call() can NO-OP when it hits
	 * TASK_TOMBSTONE. In that case we must already have been detached
	 * from the context (by perf_event_exit_event()) but the grouping
	 * might still be in-tact.
	 */
	WARN_ON_ONCE(event->attach_state & PERF_ATTACH_CONTEXT);
	if ((flags & DETACH_GROUP) &&
	    (event->attach_state & PERF_ATTACH_GROUP)) {
		/*
		 * Since in that case we cannot possibly be scheduled, simply
		 * detach now.
		 */
		raw_spin_lock_irq(&ctx->lock);
		perf_group_detach(event);
		raw_spin_unlock_irq(&ctx->lock);
	}
}
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
struct task_struct {int dummy; } ;
struct perf_event_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  is_active; } ;
struct perf_event {int /*<<< orphan*/  child_mutex; int /*<<< orphan*/  child_list; TYPE_1__* ctx; struct perf_event* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EVENT_STATE_EXIT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_event (struct perf_event*) ; 
 int /*<<< orphan*/  list_del_event (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_set_state (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_wakeup (struct perf_event*) ; 
 int /*<<< orphan*/  perf_group_detach (struct perf_event*) ; 
 int /*<<< orphan*/  put_event (struct perf_event*) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_child_event (struct perf_event*,struct task_struct*) ; 

__attribute__((used)) static void
perf_event_exit_event(struct perf_event *child_event,
		      struct perf_event_context *child_ctx,
		      struct task_struct *child)
{
	struct perf_event *parent_event = child_event->parent;

	/*
	 * Do not destroy the 'original' grouping; because of the context
	 * switch optimization the original events could've ended up in a
	 * random child task.
	 *
	 * If we were to destroy the original group, all group related
	 * operations would cease to function properly after this random
	 * child dies.
	 *
	 * Do destroy all inherited groups, we don't care about those
	 * and being thorough is better.
	 */
	raw_spin_lock_irq(&child_ctx->lock);
	WARN_ON_ONCE(child_ctx->is_active);

	if (parent_event)
		perf_group_detach(child_event);
	list_del_event(child_event, child_ctx);
	perf_event_set_state(child_event, PERF_EVENT_STATE_EXIT); /* is_event_hup() */
	raw_spin_unlock_irq(&child_ctx->lock);

	/*
	 * Parent events are governed by their filedesc, retain them.
	 */
	if (!parent_event) {
		perf_event_wakeup(child_event);
		return;
	}
	/*
	 * Child events can be cleaned up.
	 */

	sync_child_event(child_event, child);

	/*
	 * Remove this event from the parent's list
	 */
	WARN_ON_ONCE(parent_event->ctx->parent_ctx);
	mutex_lock(&parent_event->child_mutex);
	list_del_init(&child_event->child_list);
	mutex_unlock(&parent_event->child_mutex);

	/*
	 * Kick perf_poll() for is_event_hup().
	 */
	perf_event_wakeup(parent_event);
	free_event(child_event);
	put_event(parent_event);
}
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
struct perf_event_context {int /*<<< orphan*/  generation; int /*<<< orphan*/  nr_stat; int /*<<< orphan*/  nr_events; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ inherit_stat; } ;
struct perf_event {int attach_state; scalar_t__ state; struct perf_event* group_leader; int /*<<< orphan*/  event_entry; TYPE_1__ attr; struct perf_event_context* ctx; } ;

/* Variables and functions */
 int PERF_ATTACH_CONTEXT ; 
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  del_event_from_groups (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_update_cgroup_event (struct perf_event*,struct perf_event_context*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_set_state (struct perf_event*,scalar_t__) ; 

__attribute__((used)) static void
list_del_event(struct perf_event *event, struct perf_event_context *ctx)
{
	WARN_ON_ONCE(event->ctx != ctx);
	lockdep_assert_held(&ctx->lock);

	/*
	 * We can have double detach due to exit/hot-unplug + close.
	 */
	if (!(event->attach_state & PERF_ATTACH_CONTEXT))
		return;

	event->attach_state &= ~PERF_ATTACH_CONTEXT;

	list_update_cgroup_event(event, ctx, false);

	ctx->nr_events--;
	if (event->attr.inherit_stat)
		ctx->nr_stat--;

	list_del_rcu(&event->event_entry);

	if (event->group_leader == event)
		del_event_from_groups(event, ctx);

	/*
	 * If event was in error state, then keep it
	 * that way, otherwise bogus counts will be
	 * returned on read(). The only way to get out
	 * of error state is by explicit re-enabling
	 * of the event
	 */
	if (event->state > PERF_EVENT_STATE_OFF)
		perf_event_set_state(event, PERF_EVENT_STATE_OFF);

	ctx->generation++;
}
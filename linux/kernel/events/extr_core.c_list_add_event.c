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
struct perf_event_context {int /*<<< orphan*/  generation; int /*<<< orphan*/  nr_stat; int /*<<< orphan*/  nr_events; int /*<<< orphan*/  event_list; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ inherit_stat; } ;
struct perf_event {int attach_state; TYPE_1__ attr; int /*<<< orphan*/  event_entry; int /*<<< orphan*/  event_caps; int /*<<< orphan*/  group_caps; struct perf_event* group_leader; int /*<<< orphan*/  tstamp; } ;

/* Variables and functions */
 int PERF_ATTACH_CONTEXT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  add_event_to_groups (struct perf_event*,struct perf_event_context*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_update_cgroup_event (struct perf_event*,struct perf_event_context*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_time (struct perf_event*) ; 

__attribute__((used)) static void
list_add_event(struct perf_event *event, struct perf_event_context *ctx)
{
	lockdep_assert_held(&ctx->lock);

	WARN_ON_ONCE(event->attach_state & PERF_ATTACH_CONTEXT);
	event->attach_state |= PERF_ATTACH_CONTEXT;

	event->tstamp = perf_event_time(event);

	/*
	 * If we're a stand alone event or group leader, we go to the context
	 * list, group events are kept attached to the group so that
	 * perf_group_detach can, at all times, locate all siblings.
	 */
	if (event->group_leader == event) {
		event->group_caps = event->event_caps;
		add_event_to_groups(event, ctx);
	}

	list_update_cgroup_event(event, ctx, true);

	list_add_rcu(&event->event_entry, &ctx->event_list);
	ctx->nr_events++;
	if (event->attr.inherit_stat)
		ctx->nr_stat++;

	ctx->generation++;
}
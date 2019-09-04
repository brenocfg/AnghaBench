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
struct sched_in_data {scalar_t__ can_add_hw; TYPE_1__* ctx; int /*<<< orphan*/  cpuctx; } ;
struct perf_event {scalar_t__ state; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  flexible_active; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  event_filter_match (struct perf_event*) ; 
 scalar_t__ group_can_go_on (struct perf_event*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  group_sched_in (struct perf_event*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flexible_sched_in(struct perf_event *event, void *data)
{
	struct sched_in_data *sid = data;

	if (event->state <= PERF_EVENT_STATE_OFF)
		return 0;

	if (!event_filter_match(event))
		return 0;

	if (group_can_go_on(event, sid->cpuctx, sid->can_add_hw)) {
		if (!group_sched_in(event, sid->cpuctx, sid->ctx))
			list_add_tail(&event->active_list, &sid->ctx->flexible_active);
		else
			sid->can_add_hw = 0;
	}

	return 0;
}
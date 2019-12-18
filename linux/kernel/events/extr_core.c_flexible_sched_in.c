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
struct sched_in_data {TYPE_1__* ctx; scalar_t__ can_add_hw; int /*<<< orphan*/  cpuctx; } ;
struct perf_event {scalar_t__ state; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {int rotate_necessary; int /*<<< orphan*/  flexible_active; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_OFF ; 
 int /*<<< orphan*/  event_filter_match (struct perf_event*) ; 
 scalar_t__ group_can_go_on (struct perf_event*,int /*<<< orphan*/ ,scalar_t__) ; 
 int group_sched_in (struct perf_event*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flexible_sched_in(struct perf_event *event, void *data)
{
	struct sched_in_data *sid = data;

	if (event->state <= PERF_EVENT_STATE_OFF)
		return 0;

	if (!event_filter_match(event))
		return 0;

	if (group_can_go_on(event, sid->cpuctx, sid->can_add_hw)) {
		int ret = group_sched_in(event, sid->cpuctx, sid->ctx);
		if (ret) {
			sid->can_add_hw = 0;
			sid->ctx->rotate_necessary = 1;
			return 0;
		}
		list_add_tail(&event->active_list, &sid->ctx->flexible_active);
	}

	return 0;
}
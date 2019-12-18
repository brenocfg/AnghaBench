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
struct perf_event_context {int /*<<< orphan*/  task; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ pinned; } ;
struct perf_event {TYPE_1__ attr; struct perf_event* group_leader; struct perf_event_context* ctx; } ;
typedef  enum event_type_t { ____Placeholder_event_type_t } event_type_t ;

/* Variables and functions */
 int EVENT_CPU ; 
 int EVENT_FLEXIBLE ; 
 int EVENT_PINNED ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum event_type_t get_event_type(struct perf_event *event)
{
	struct perf_event_context *ctx = event->ctx;
	enum event_type_t event_type;

	lockdep_assert_held(&ctx->lock);

	/*
	 * It's 'group type', really, because if our group leader is
	 * pinned, so are we.
	 */
	if (event->group_leader != event)
		event = event->group_leader;

	event_type = event->attr.pinned ? EVENT_PINNED : EVENT_FLEXIBLE;
	if (!ctx->task)
		event_type |= EVENT_CPU;

	return event_type;
}
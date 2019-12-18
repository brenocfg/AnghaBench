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
struct perf_event_groups {int /*<<< orphan*/  tree; } ;
struct perf_event {int /*<<< orphan*/  group_node; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  init_event_group (struct perf_event*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
perf_event_groups_delete(struct perf_event_groups *groups,
			 struct perf_event *event)
{
	WARN_ON_ONCE(RB_EMPTY_NODE(&event->group_node) ||
		     RB_EMPTY_ROOT(&groups->tree));

	rb_erase(&event->group_node, &groups->tree);
	init_event_group(event);
}
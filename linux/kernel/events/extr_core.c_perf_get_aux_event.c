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
struct perf_event {struct perf_event* aux_event; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_aux_output_match (struct perf_event*,struct perf_event*) ; 

__attribute__((used)) static int perf_get_aux_event(struct perf_event *event,
			      struct perf_event *group_leader)
{
	/*
	 * Our group leader must be an aux event if we want to be
	 * an aux_output. This way, the aux event will precede its
	 * aux_output events in the group, and therefore will always
	 * schedule first.
	 */
	if (!group_leader)
		return 0;

	if (!perf_aux_output_match(event, group_leader))
		return 0;

	if (!atomic_long_inc_not_zero(&group_leader->refcount))
		return 0;

	/*
	 * Link aux_outputs to their aux event; this is undone in
	 * perf_group_detach() by perf_put_aux_event(). When the
	 * group in torn down, the aux_output events loose their
	 * link to the aux_event and can't schedule any more.
	 */
	event->aux_event = group_leader;

	return 1;
}
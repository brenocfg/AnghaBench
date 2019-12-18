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
struct parse_events_state {int /*<<< orphan*/  idx; } ;
struct list_head {int dummy; } ;
typedef  enum perf_tool_event { ____Placeholder_perf_tool_event } perf_tool_event ;

/* Variables and functions */
 int add_event_tool (struct list_head*,int /*<<< orphan*/ *,int) ; 

int parse_events_add_tool(struct parse_events_state *parse_state,
			  struct list_head *list,
			  enum perf_tool_event tool_event)
{
	return add_event_tool(list, &parse_state->idx, tool_event);
}
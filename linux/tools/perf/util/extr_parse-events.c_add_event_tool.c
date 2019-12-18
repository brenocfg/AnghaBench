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
struct perf_event_attr {int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct list_head {int dummy; } ;
struct evsel {int tool_event; int /*<<< orphan*/  unit; } ;
typedef  enum perf_tool_event { ____Placeholder_perf_tool_event } perf_tool_event ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_COUNT_SW_DUMMY ; 
 int PERF_TOOL_DURATION_TIME ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 struct evsel* __add_event (struct list_head*,int*,struct perf_event_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int add_event_tool(struct list_head *list, int *idx,
			  enum perf_tool_event tool_event)
{
	struct evsel *evsel;
	struct perf_event_attr attr = {
		.type = PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_DUMMY,
	};

	evsel = __add_event(list, idx, &attr, NULL, NULL, NULL, false, "0");
	if (!evsel)
		return -ENOMEM;
	evsel->tool_event = tool_event;
	if (tool_event == PERF_TOOL_DURATION_TIME)
		evsel->unit = strdup("ns");
	return 0;
}
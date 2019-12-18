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
typedef  union perf_event {int dummy; } perf_event ;
struct TYPE_2__ {int /*<<< orphan*/  last; int /*<<< orphan*/  data; } ;
struct trace {TYPE_1__ oe; int /*<<< orphan*/  evlist; int /*<<< orphan*/  sort_events; } ;

/* Variables and functions */
 int __trace__deliver_event (struct trace*,union perf_event*) ; 
 int ordered_events__queue (int /*<<< orphan*/ *,union perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_evlist__parse_sample_timestamp (int /*<<< orphan*/ ,union perf_event*,int /*<<< orphan*/ *) ; 
 int trace__flush_events (struct trace*) ; 

__attribute__((used)) static int trace__deliver_event(struct trace *trace, union perf_event *event)
{
	int err;

	if (!trace->sort_events)
		return __trace__deliver_event(trace, event);

	err = perf_evlist__parse_sample_timestamp(trace->evlist, event, &trace->oe.last);
	if (err && err != -1)
		return err;

	err = ordered_events__queue(&trace->oe.data, event, trace->oe.last, 0);
	if (err)
		return err;

	return trace__flush_events(trace);
}
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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
union perf_event {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_trace ; 
 int /*<<< orphan*/  print_binary (unsigned char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,union perf_event*) ; 
 int /*<<< orphan*/  trace_event_printer ; 

void trace_event(union perf_event *event)
{
	unsigned char *raw_event = (void *)event;

	if (!dump_trace)
		return;

	print_binary(raw_event, event->header.size, 16,
		     trace_event_printer, event);
}
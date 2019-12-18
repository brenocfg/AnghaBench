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
struct TYPE_2__ {int misc; } ;
union perf_event {TYPE_1__ header; } ;
struct perf_tool {int dummy; } ;
struct perf_sample {int pid; int tid; int time; int stream_id; int cpu; int period; int cpumode; } ;
struct machine {int dummy; } ;
typedef  int (* perf_event__handler_t ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ;

/* Variables and functions */
 int PERF_RECORD_MISC_CPUMODE_MASK ; 

int perf_tool__process_synth_event(struct perf_tool *tool,
				   union perf_event *event,
				   struct machine *machine,
				   perf_event__handler_t process)
{
	struct perf_sample synth_sample = {
		.pid	   = -1,
		.tid	   = -1,
		.time	   = -1,
		.stream_id = -1,
		.cpu	   = -1,
		.period	   = 1,
		.cpumode   = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK,
	};

	return process(tool, event, &synth_sample, machine);
}
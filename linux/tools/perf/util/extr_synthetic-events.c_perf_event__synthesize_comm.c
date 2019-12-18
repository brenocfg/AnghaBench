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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_tool {int dummy; } ;
struct machine {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;

/* Variables and functions */
 scalar_t__ perf_event__prepare_comm (union perf_event*,int,struct machine*,int*,int*) ; 
 scalar_t__ perf_tool__process_synth_event (struct perf_tool*,union perf_event*,struct machine*,int /*<<< orphan*/ ) ; 

pid_t perf_event__synthesize_comm(struct perf_tool *tool,
					 union perf_event *event, pid_t pid,
					 perf_event__handler_t process,
					 struct machine *machine)
{
	pid_t tgid, ppid;

	if (perf_event__prepare_comm(event, pid, machine, &tgid, &ppid) != 0)
		return -1;

	if (perf_tool__process_synth_event(tool, event, machine, process) != 0)
		return -1;

	return tgid;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  misc; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ header; scalar_t__ tid; scalar_t__ pid; scalar_t__ ptid; scalar_t__ ppid; } ;
union perf_event {TYPE_2__ fork; } ;
struct perf_tool {int dummy; } ;
struct machine {scalar_t__ id_hdr_size; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_FORK ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_FORK_EXEC ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ perf_tool__process_synth_event (struct perf_tool*,union perf_event*,struct machine*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_event__synthesize_fork(struct perf_tool *tool,
				       union perf_event *event,
				       pid_t pid, pid_t tgid, pid_t ppid,
				       perf_event__handler_t process,
				       struct machine *machine)
{
	memset(&event->fork, 0, sizeof(event->fork) + machine->id_hdr_size);

	/*
	 * for main thread set parent to ppid from status file. For other
	 * threads set parent pid to main thread. ie., assume main thread
	 * spawns all threads in a process
	*/
	if (tgid == pid) {
		event->fork.ppid = ppid;
		event->fork.ptid = ppid;
	} else {
		event->fork.ppid = tgid;
		event->fork.ptid = tgid;
	}
	event->fork.pid  = tgid;
	event->fork.tid  = pid;
	event->fork.header.type = PERF_RECORD_FORK;
	event->fork.header.misc = PERF_RECORD_MISC_FORK_EXEC;

	event->fork.header.size = (sizeof(event->fork) + machine->id_hdr_size);

	if (perf_tool__process_synth_event(tool, event, machine, process) != 0)
		return -1;

	return 0;
}
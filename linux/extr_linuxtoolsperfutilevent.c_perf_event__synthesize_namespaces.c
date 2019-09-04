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
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int nr_namespaces; TYPE_1__ header; struct perf_ns_link_info* link_info; void* tid; void* pid; } ;
union perf_event {TYPE_2__ namespaces; } ;
typedef  size_t u32 ;
struct perf_tool {int /*<<< orphan*/  namespace_events; } ;
struct perf_ns_link_info {int dummy; } ;
struct machine {scalar_t__ id_hdr_size; } ;
typedef  void* pid_t ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;

/* Variables and functions */
 int NR_NAMESPACES ; 
 int /*<<< orphan*/  PERF_RECORD_NAMESPACES ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  perf_event__get_ns_link_info (void*,int /*<<< orphan*/ ,struct perf_ns_link_info*) ; 
 int /*<<< orphan*/  perf_ns__name (size_t) ; 
 scalar_t__ perf_tool__process_synth_event (struct perf_tool*,union perf_event*,struct machine*,int /*<<< orphan*/ ) ; 

int perf_event__synthesize_namespaces(struct perf_tool *tool,
				      union perf_event *event,
				      pid_t pid, pid_t tgid,
				      perf_event__handler_t process,
				      struct machine *machine)
{
	u32 idx;
	struct perf_ns_link_info *ns_link_info;

	if (!tool || !tool->namespace_events)
		return 0;

	memset(&event->namespaces, 0, (sizeof(event->namespaces) +
	       (NR_NAMESPACES * sizeof(struct perf_ns_link_info)) +
	       machine->id_hdr_size));

	event->namespaces.pid = tgid;
	event->namespaces.tid = pid;

	event->namespaces.nr_namespaces = NR_NAMESPACES;

	ns_link_info = event->namespaces.link_info;

	for (idx = 0; idx < event->namespaces.nr_namespaces; idx++)
		perf_event__get_ns_link_info(pid, perf_ns__name(idx),
					     &ns_link_info[idx]);

	event->namespaces.header.type = PERF_RECORD_NAMESPACES;

	event->namespaces.header.size = (sizeof(event->namespaces) +
			(NR_NAMESPACES * sizeof(struct perf_ns_link_info)) +
			machine->id_hdr_size);

	if (perf_tool__process_synth_event(tool, event, machine, process) != 0)
		return -1;

	return 0;
}
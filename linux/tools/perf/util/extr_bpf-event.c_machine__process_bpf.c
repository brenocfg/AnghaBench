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
struct TYPE_2__ {int type; } ;
union perf_event {TYPE_1__ bpf; } ;
struct perf_sample {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
#define  PERF_BPF_EVENT_PROG_LOAD 129 
#define  PERF_BPF_EVENT_PROG_UNLOAD 128 
 scalar_t__ dump_trace ; 
 int machine__process_bpf_event_load (struct machine*,union perf_event*,struct perf_sample*) ; 
 int /*<<< orphan*/  perf_event__fprintf_bpf (union perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  stdout ; 

int machine__process_bpf(struct machine *machine, union perf_event *event,
			 struct perf_sample *sample)
{
	if (dump_trace)
		perf_event__fprintf_bpf(event, stdout);

	switch (event->bpf.type) {
	case PERF_BPF_EVENT_PROG_LOAD:
		return machine__process_bpf_event_load(machine, event, sample);

	case PERF_BPF_EVENT_PROG_UNLOAD:
		/*
		 * Do not free bpf_prog_info and btf of the program here,
		 * as annotation still need them. They will be freed at
		 * the end of the session.
		 */
		break;
	default:
		pr_debug("unexpected bpf event type of %d\n", event->bpf.type);
		break;
	}
	return 0;
}
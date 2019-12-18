#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nr; int /*<<< orphan*/  entries; scalar_t__ map; } ;
struct trace {TYPE_3__* evlist; TYPE_2__ filter_pids; } ;
struct TYPE_4__ {int /*<<< orphan*/  threads; } ;
struct TYPE_6__ {TYPE_1__ core; } ;

/* Variables and functions */
 int bpf_map__set_filter_pids (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int perf_evlist__set_tp_filter_pids (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int perf_thread_map__pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trace__set_filter_loop_pids (struct trace*) ; 

__attribute__((used)) static int trace__set_filter_pids(struct trace *trace)
{
	int err = 0;
	/*
	 * Better not use !target__has_task() here because we need to cover the
	 * case where no threads were specified in the command line, but a
	 * workload was, and in that case we will fill in the thread_map when
	 * we fork the workload in perf_evlist__prepare_workload.
	 */
	if (trace->filter_pids.nr > 0) {
		err = perf_evlist__set_tp_filter_pids(trace->evlist, trace->filter_pids.nr,
						      trace->filter_pids.entries);
		if (!err && trace->filter_pids.map) {
			err = bpf_map__set_filter_pids(trace->filter_pids.map, trace->filter_pids.nr,
						       trace->filter_pids.entries);
		}
	} else if (perf_thread_map__pid(trace->evlist->core.threads, 0) == -1) {
		err = trace__set_filter_loop_pids(trace);
	}

	return err;
}
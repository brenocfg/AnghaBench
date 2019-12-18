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
struct perf_sample {int dummy; } ;
struct machine {int dummy; } ;
struct evsel {int (* handler ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct evsel*,struct machine*) ;} ;
typedef  int (* inject_handler ) (struct perf_tool*,union perf_event*,struct perf_sample*,struct evsel*,struct machine*) ;

/* Variables and functions */
 int /*<<< orphan*/  build_id__mark_dso_hit (struct perf_tool*,union perf_event*,struct perf_sample*,struct evsel*,struct machine*) ; 
 int perf_event__repipe_synth (struct perf_tool*,union perf_event*) ; 

__attribute__((used)) static int perf_event__repipe_sample(struct perf_tool *tool,
				     union perf_event *event,
				     struct perf_sample *sample,
				     struct evsel *evsel,
				     struct machine *machine)
{
	if (evsel && evsel->handler) {
		inject_handler f = evsel->handler;
		return f(tool, event, sample, evsel, machine);
	}

	build_id__mark_dso_hit(tool, event, sample, evsel, machine);

	return perf_event__repipe_synth(tool, event);
}
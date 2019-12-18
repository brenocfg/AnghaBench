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
struct evsel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpus; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_cpu_map__empty (int /*<<< orphan*/ ) ; 
 int perf_evlist__enable_event_cpu (struct evlist*,struct evsel*,int) ; 
 int perf_evlist__enable_event_thread (struct evlist*,struct evsel*,int) ; 

int perf_evlist__enable_event_idx(struct evlist *evlist,
				  struct evsel *evsel, int idx)
{
	bool per_cpu_mmaps = !perf_cpu_map__empty(evlist->core.cpus);

	if (per_cpu_mmaps)
		return perf_evlist__enable_event_cpu(evlist, evsel, idx);
	else
		return perf_evlist__enable_event_thread(evlist, evsel, idx);
}
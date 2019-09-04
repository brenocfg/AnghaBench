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
struct perf_evsel {int dummy; } ;
struct perf_evlist {int /*<<< orphan*/  cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_map__empty (int /*<<< orphan*/ ) ; 
 int perf_evlist__enable_event_cpu (struct perf_evlist*,struct perf_evsel*,int) ; 
 int perf_evlist__enable_event_thread (struct perf_evlist*,struct perf_evsel*,int) ; 

int perf_evlist__enable_event_idx(struct perf_evlist *evlist,
				  struct perf_evsel *evsel, int idx)
{
	bool per_cpu_mmaps = !cpu_map__empty(evlist->cpus);

	if (per_cpu_mmaps)
		return perf_evlist__enable_event_cpu(evlist, evsel, idx);
	else
		return perf_evlist__enable_event_thread(evlist, evsel, idx);
}
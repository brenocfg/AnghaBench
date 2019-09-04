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
struct perf_evsel {scalar_t__ own_cpus; scalar_t__ cpus; int /*<<< orphan*/  threads; } ;
struct perf_evlist {scalar_t__ cpus; int /*<<< orphan*/  threads; scalar_t__ has_user_cpus; } ;

/* Variables and functions */
 void* cpu_map__get (scalar_t__) ; 
 int /*<<< orphan*/  cpu_map__put (scalar_t__) ; 
 int /*<<< orphan*/  thread_map__get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_map__put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __perf_evlist__propagate_maps(struct perf_evlist *evlist,
					  struct perf_evsel *evsel)
{
	/*
	 * We already have cpus for evsel (via PMU sysfs) so
	 * keep it, if there's no target cpu list defined.
	 */
	if (!evsel->own_cpus || evlist->has_user_cpus) {
		cpu_map__put(evsel->cpus);
		evsel->cpus = cpu_map__get(evlist->cpus);
	} else if (evsel->cpus != evsel->own_cpus) {
		cpu_map__put(evsel->cpus);
		evsel->cpus = cpu_map__get(evsel->own_cpus);
	}

	thread_map__put(evsel->threads);
	evsel->threads = thread_map__get(evlist->threads);
}
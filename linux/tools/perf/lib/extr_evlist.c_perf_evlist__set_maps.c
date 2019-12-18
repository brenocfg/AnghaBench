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
struct perf_thread_map {int dummy; } ;
struct perf_evlist {struct perf_thread_map* threads; struct perf_cpu_map* cpus; } ;
struct perf_cpu_map {int dummy; } ;

/* Variables and functions */
 struct perf_cpu_map* perf_cpu_map__get (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  perf_evlist__propagate_maps (struct perf_evlist*) ; 
 struct perf_thread_map* perf_thread_map__get (struct perf_thread_map*) ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 

void perf_evlist__set_maps(struct perf_evlist *evlist,
			   struct perf_cpu_map *cpus,
			   struct perf_thread_map *threads)
{
	/*
	 * Allow for the possibility that one or another of the maps isn't being
	 * changed i.e. don't put it.  Note we are assuming the maps that are
	 * being applied are brand new and evlist is taking ownership of the
	 * original reference count of 1.  If that is not the case it is up to
	 * the caller to increase the reference count.
	 */
	if (cpus != evlist->cpus) {
		perf_cpu_map__put(evlist->cpus);
		evlist->cpus = perf_cpu_map__get(cpus);
	}

	if (threads != evlist->threads) {
		perf_thread_map__put(evlist->threads);
		evlist->threads = perf_thread_map__get(threads);
	}

	perf_evlist__propagate_maps(evlist);
}
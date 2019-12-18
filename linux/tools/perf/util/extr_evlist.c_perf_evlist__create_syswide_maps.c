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
struct perf_cpu_map {int dummy; } ;
struct evlist {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  perf_evlist__set_maps (int /*<<< orphan*/ *,struct perf_cpu_map*,struct perf_thread_map*) ; 
 struct perf_thread_map* perf_thread_map__new_dummy () ; 

__attribute__((used)) static int perf_evlist__create_syswide_maps(struct evlist *evlist)
{
	struct perf_cpu_map *cpus;
	struct perf_thread_map *threads;
	int err = -ENOMEM;

	/*
	 * Try reading /sys/devices/system/cpu/online to get
	 * an all cpus map.
	 *
	 * FIXME: -ENOMEM is the best we can do here, the cpu_map
	 * code needs an overhaul to properly forward the
	 * error, and we may not want to do that fallback to a
	 * default cpu identity map :-\
	 */
	cpus = perf_cpu_map__new(NULL);
	if (!cpus)
		goto out;

	threads = perf_thread_map__new_dummy();
	if (!threads)
		goto out_put;

	perf_evlist__set_maps(&evlist->core, cpus, threads);
out:
	return err;
out_put:
	perf_cpu_map__put(cpus);
	goto out;
}
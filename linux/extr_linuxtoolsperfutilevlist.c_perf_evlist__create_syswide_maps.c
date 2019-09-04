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
struct thread_map {int dummy; } ;
struct perf_evlist {int dummy; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cpu_map* cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_map__put (struct cpu_map*) ; 
 int /*<<< orphan*/  perf_evlist__set_maps (struct perf_evlist*,struct cpu_map*,struct thread_map*) ; 
 struct thread_map* thread_map__new_dummy () ; 

__attribute__((used)) static int perf_evlist__create_syswide_maps(struct perf_evlist *evlist)
{
	struct cpu_map	  *cpus;
	struct thread_map *threads;
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
	cpus = cpu_map__new(NULL);
	if (!cpus)
		goto out;

	threads = thread_map__new_dummy();
	if (!threads)
		goto out_put;

	perf_evlist__set_maps(evlist, cpus, threads);
out:
	return err;
out_put:
	cpu_map__put(cpus);
	goto out;
}
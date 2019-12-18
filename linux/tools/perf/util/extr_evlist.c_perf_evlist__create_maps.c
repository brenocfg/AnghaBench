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
struct target {int /*<<< orphan*/  cpu_list; int /*<<< orphan*/  uid; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; scalar_t__ system_wide; scalar_t__ per_thread; } ;
struct perf_thread_map {int dummy; } ;
struct perf_cpu_map {int dummy; } ;
struct TYPE_2__ {int has_user_cpus; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 struct perf_cpu_map* perf_cpu_map__dummy_new () ; 
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__set_maps (TYPE_1__*,struct perf_cpu_map*,struct perf_thread_map*) ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 
 scalar_t__ target__uses_dummy_map (struct target*) ; 
 struct perf_thread_map* thread_map__new_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int perf_evlist__create_maps(struct evlist *evlist, struct target *target)
{
	bool all_threads = (target->per_thread && target->system_wide);
	struct perf_cpu_map *cpus;
	struct perf_thread_map *threads;

	/*
	 * If specify '-a' and '--per-thread' to perf record, perf record
	 * will override '--per-thread'. target->per_thread = false and
	 * target->system_wide = true.
	 *
	 * If specify '--per-thread' only to perf record,
	 * target->per_thread = true and target->system_wide = false.
	 *
	 * So target->per_thread && target->system_wide is false.
	 * For perf record, thread_map__new_str doesn't call
	 * thread_map__new_all_cpus. That will keep perf record's
	 * current behavior.
	 *
	 * For perf stat, it allows the case that target->per_thread and
	 * target->system_wide are all true. It means to collect system-wide
	 * per-thread data. thread_map__new_str will call
	 * thread_map__new_all_cpus to enumerate all threads.
	 */
	threads = thread_map__new_str(target->pid, target->tid, target->uid,
				      all_threads);

	if (!threads)
		return -1;

	if (target__uses_dummy_map(target))
		cpus = perf_cpu_map__dummy_new();
	else
		cpus = perf_cpu_map__new(target->cpu_list);

	if (!cpus)
		goto out_delete_threads;

	evlist->core.has_user_cpus = !!target->cpu_list;

	perf_evlist__set_maps(&evlist->core, cpus, threads);

	return 0;

out_delete_threads:
	perf_thread_map__put(threads);
	return -1;
}
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
struct target {int /*<<< orphan*/  cpu_list; int /*<<< orphan*/  uid; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; scalar_t__ system_wide; scalar_t__ per_thread; } ;
struct perf_evlist {int has_user_cpus; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */
 struct cpu_map* cpu_map__dummy_new () ; 
 struct cpu_map* cpu_map__new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__set_maps (struct perf_evlist*,struct cpu_map*,struct thread_map*) ; 
 scalar_t__ target__uses_dummy_map (struct target*) ; 
 struct thread_map* thread_map__new_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread_map__put (struct thread_map*) ; 

int perf_evlist__create_maps(struct perf_evlist *evlist, struct target *target)
{
	bool all_threads = (target->per_thread && target->system_wide);
	struct cpu_map *cpus;
	struct thread_map *threads;

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
		cpus = cpu_map__dummy_new();
	else
		cpus = cpu_map__new(target->cpu_list);

	if (!cpus)
		goto out_delete_threads;

	evlist->has_user_cpus = !!target->cpu_list;

	perf_evlist__set_maps(evlist, cpus, threads);

	return 0;

out_delete_threads:
	thread_map__put(threads);
	return -1;
}
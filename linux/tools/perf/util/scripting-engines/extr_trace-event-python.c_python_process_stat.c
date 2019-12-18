#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct perf_thread_map {int nr; } ;
struct perf_stat_config {scalar_t__ aggr_mode; } ;
struct perf_cpu_map {int nr; int* map; } ;
struct TYPE_3__ {struct perf_cpu_map* cpus; struct perf_thread_map* threads; } ;
struct evsel {TYPE_2__* counts; TYPE_1__ core; } ;
struct TYPE_4__ {int /*<<< orphan*/  aggr; } ;

/* Variables and functions */
 scalar_t__ AGGR_GLOBAL ; 
 int /*<<< orphan*/ * perf_counts (TYPE_2__*,int,int) ; 
 int perf_thread_map__pid (struct perf_thread_map*,int) ; 
 int /*<<< orphan*/  process_stat (struct evsel*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void python_process_stat(struct perf_stat_config *config,
				struct evsel *counter, u64 tstamp)
{
	struct perf_thread_map *threads = counter->core.threads;
	struct perf_cpu_map *cpus = counter->core.cpus;
	int cpu, thread;

	if (config->aggr_mode == AGGR_GLOBAL) {
		process_stat(counter, -1, -1, tstamp,
			     &counter->counts->aggr);
		return;
	}

	for (thread = 0; thread < threads->nr; thread++) {
		for (cpu = 0; cpu < cpus->nr; cpu++) {
			process_stat(counter, cpus->map[cpu],
				     perf_thread_map__pid(threads, thread), tstamp,
				     perf_counts(counter->counts, cpu, thread));
		}
	}
}
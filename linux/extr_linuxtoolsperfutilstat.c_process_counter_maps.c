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
struct perf_stat_config {int dummy; } ;
struct perf_evsel {int /*<<< orphan*/  counts; scalar_t__ system_wide; int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_counts (int /*<<< orphan*/ ,int,int) ; 
 int perf_evsel__nr_cpus (struct perf_evsel*) ; 
 scalar_t__ process_counter_values (struct perf_stat_config*,struct perf_evsel*,int,int,int /*<<< orphan*/ ) ; 
 int thread_map__nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_counter_maps(struct perf_stat_config *config,
				struct perf_evsel *counter)
{
	int nthreads = thread_map__nr(counter->threads);
	int ncpus = perf_evsel__nr_cpus(counter);
	int cpu, thread;

	if (counter->system_wide)
		nthreads = 1;

	for (thread = 0; thread < nthreads; thread++) {
		for (cpu = 0; cpu < ncpus; cpu++) {
			if (process_counter_values(config, counter, cpu, thread,
						   perf_counts(counter->counts, cpu, thread)))
				return -1;
		}
	}

	return 0;
}
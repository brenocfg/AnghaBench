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
struct perf_evlist {int /*<<< orphan*/  threads; int /*<<< orphan*/  cpus; } ;
struct mmap_params {int /*<<< orphan*/  auxtrace_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace_mmap_params__set_idx (int /*<<< orphan*/ *,struct perf_evlist*,int,int) ; 
 int cpu_map__nr (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evlist__mmap_per_evsel (struct perf_evlist*,int,struct mmap_params*,int,int,int*,int*) ; 
 int /*<<< orphan*/  perf_evlist__munmap_nofree (struct perf_evlist*) ; 
 int /*<<< orphan*/  pr_debug2 (char*) ; 
 int thread_map__nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evlist__mmap_per_cpu(struct perf_evlist *evlist,
				     struct mmap_params *mp)
{
	int cpu, thread;
	int nr_cpus = cpu_map__nr(evlist->cpus);
	int nr_threads = thread_map__nr(evlist->threads);

	pr_debug2("perf event ring buffer mmapped per cpu\n");
	for (cpu = 0; cpu < nr_cpus; cpu++) {
		int output = -1;
		int output_overwrite = -1;

		auxtrace_mmap_params__set_idx(&mp->auxtrace_mp, evlist, cpu,
					      true);

		for (thread = 0; thread < nr_threads; thread++) {
			if (perf_evlist__mmap_per_evsel(evlist, cpu, mp, cpu,
							thread, &output, &output_overwrite))
				goto out_unmap;
		}
	}

	return 0;

out_unmap:
	perf_evlist__munmap_nofree(evlist);
	return -1;
}
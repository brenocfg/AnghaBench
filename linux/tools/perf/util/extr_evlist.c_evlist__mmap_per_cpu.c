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
struct mmap_params {int /*<<< orphan*/  auxtrace_mp; } ;
struct TYPE_2__ {int /*<<< orphan*/  threads; int /*<<< orphan*/  cpus; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace_mmap_params__set_idx (int /*<<< orphan*/ *,struct evlist*,int,int) ; 
 scalar_t__ evlist__mmap_per_evsel (struct evlist*,int,struct mmap_params*,int,int,int*,int*) ; 
 int /*<<< orphan*/  evlist__munmap_nofree (struct evlist*) ; 
 int perf_cpu_map__nr (int /*<<< orphan*/ ) ; 
 int perf_thread_map__nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug2 (char*) ; 

__attribute__((used)) static int evlist__mmap_per_cpu(struct evlist *evlist,
				     struct mmap_params *mp)
{
	int cpu, thread;
	int nr_cpus = perf_cpu_map__nr(evlist->core.cpus);
	int nr_threads = perf_thread_map__nr(evlist->core.threads);

	pr_debug2("perf event ring buffer mmapped per cpu\n");
	for (cpu = 0; cpu < nr_cpus; cpu++) {
		int output = -1;
		int output_overwrite = -1;

		auxtrace_mmap_params__set_idx(&mp->auxtrace_mp, evlist, cpu,
					      true);

		for (thread = 0; thread < nr_threads; thread++) {
			if (evlist__mmap_per_evsel(evlist, cpu, mp, cpu,
							thread, &output, &output_overwrite))
				goto out_unmap;
		}
	}

	return 0;

out_unmap:
	evlist__munmap_nofree(evlist);
	return -1;
}
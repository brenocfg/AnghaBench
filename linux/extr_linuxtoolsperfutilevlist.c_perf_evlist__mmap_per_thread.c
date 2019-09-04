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
struct perf_evlist {int /*<<< orphan*/  threads; } ;
struct mmap_params {int /*<<< orphan*/  auxtrace_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace_mmap_params__set_idx (int /*<<< orphan*/ *,struct perf_evlist*,int,int) ; 
 scalar_t__ perf_evlist__mmap_per_evsel (struct perf_evlist*,int,struct mmap_params*,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  perf_evlist__munmap_nofree (struct perf_evlist*) ; 
 int /*<<< orphan*/  pr_debug2 (char*) ; 
 int thread_map__nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evlist__mmap_per_thread(struct perf_evlist *evlist,
					struct mmap_params *mp)
{
	int thread;
	int nr_threads = thread_map__nr(evlist->threads);

	pr_debug2("perf event ring buffer mmapped per thread\n");
	for (thread = 0; thread < nr_threads; thread++) {
		int output = -1;
		int output_overwrite = -1;

		auxtrace_mmap_params__set_idx(&mp->auxtrace_mp, evlist, thread,
					      false);

		if (perf_evlist__mmap_per_evsel(evlist, thread, mp, 0, thread,
						&output, &output_overwrite))
			goto out_unmap;
	}

	return 0;

out_unmap:
	perf_evlist__munmap_nofree(evlist);
	return -1;
}
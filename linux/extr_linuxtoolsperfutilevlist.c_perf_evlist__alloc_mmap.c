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
struct perf_mmap {int fd; int overwrite; int /*<<< orphan*/  refcnt; } ;
struct perf_evlist {int nr_mmaps; int /*<<< orphan*/  threads; int /*<<< orphan*/  cpus; } ;

/* Variables and functions */
 scalar_t__ cpu_map__empty (int /*<<< orphan*/ ) ; 
 int cpu_map__nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int thread_map__nr (int /*<<< orphan*/ ) ; 
 struct perf_mmap* zalloc (int) ; 

__attribute__((used)) static struct perf_mmap *perf_evlist__alloc_mmap(struct perf_evlist *evlist,
						 bool overwrite)
{
	int i;
	struct perf_mmap *map;

	evlist->nr_mmaps = cpu_map__nr(evlist->cpus);
	if (cpu_map__empty(evlist->cpus))
		evlist->nr_mmaps = thread_map__nr(evlist->threads);
	map = zalloc(evlist->nr_mmaps * sizeof(struct perf_mmap));
	if (!map)
		return NULL;

	for (i = 0; i < evlist->nr_mmaps; i++) {
		map[i].fd = -1;
		map[i].overwrite = overwrite;
		/*
		 * When the perf_mmap() call is made we grab one refcount, plus
		 * one extra to let perf_mmap__consume() get the last
		 * events after all real references (perf_mmap__get()) are
		 * dropped.
		 *
		 * Each PERF_EVENT_IOC_SET_OUTPUT points to this mmap and
		 * thus does perf_mmap__get() on it.
		 */
		refcount_set(&map[i].refcnt, 0);
	}
	return map;
}
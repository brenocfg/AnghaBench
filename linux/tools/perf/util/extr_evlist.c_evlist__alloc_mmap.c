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
struct TYPE_4__ {int fd; int overwrite; int /*<<< orphan*/  refcnt; } ;
struct mmap {TYPE_2__ core; } ;
struct TYPE_3__ {int nr_mmaps; int /*<<< orphan*/  threads; int /*<<< orphan*/  cpus; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ perf_cpu_map__empty (int /*<<< orphan*/ ) ; 
 int perf_cpu_map__nr (int /*<<< orphan*/ ) ; 
 int perf_thread_map__nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mmap* zalloc (int) ; 

__attribute__((used)) static struct mmap *evlist__alloc_mmap(struct evlist *evlist,
				       bool overwrite)
{
	int i;
	struct mmap *map;

	evlist->core.nr_mmaps = perf_cpu_map__nr(evlist->core.cpus);
	if (perf_cpu_map__empty(evlist->core.cpus))
		evlist->core.nr_mmaps = perf_thread_map__nr(evlist->core.threads);
	map = zalloc(evlist->core.nr_mmaps * sizeof(struct mmap));
	if (!map)
		return NULL;

	for (i = 0; i < evlist->core.nr_mmaps; i++) {
		map[i].core.fd = -1;
		map[i].core.overwrite = overwrite;
		/*
		 * When the perf_mmap() call is made we grab one refcount, plus
		 * one extra to let perf_mmap__consume() get the last
		 * events after all real references (perf_mmap__get()) are
		 * dropped.
		 *
		 * Each PERF_EVENT_IOC_SET_OUTPUT points to this mmap and
		 * thus does perf_mmap__get() on it.
		 */
		refcount_set(&map[i].core.refcnt, 0);
	}
	return map;
}
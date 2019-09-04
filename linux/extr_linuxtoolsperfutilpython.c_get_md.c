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
struct perf_mmap {int cpu; } ;
struct perf_evlist {int nr_mmaps; struct perf_mmap* mmap; } ;

/* Variables and functions */

__attribute__((used)) static struct perf_mmap *get_md(struct perf_evlist *evlist, int cpu)
{
	int i;

	for (i = 0; i < evlist->nr_mmaps; i++) {
		struct perf_mmap *md = &evlist->mmap[i];

		if (md->cpu == cpu)
			return md;
	}

	return NULL;
}
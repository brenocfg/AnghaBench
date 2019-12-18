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
struct TYPE_2__ {int nr_mmaps; } ;
struct evlist {int /*<<< orphan*/ * overwrite_mmap; TYPE_1__ core; int /*<<< orphan*/ * mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_mmap__munmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void evlist__munmap_nofree(struct evlist *evlist)
{
	int i;

	if (evlist->mmap)
		for (i = 0; i < evlist->core.nr_mmaps; i++)
			perf_mmap__munmap(&evlist->mmap[i]);

	if (evlist->overwrite_mmap)
		for (i = 0; i < evlist->core.nr_mmaps; i++)
			perf_mmap__munmap(&evlist->overwrite_mmap[i]);
}
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
struct TYPE_4__ {int cpu; } ;
struct mmap {TYPE_2__ core; } ;
struct TYPE_3__ {int nr_mmaps; } ;
struct evlist {struct mmap* mmap; TYPE_1__ core; } ;

/* Variables and functions */

__attribute__((used)) static struct mmap *get_md(struct evlist *evlist, int cpu)
{
	int i;

	for (i = 0; i < evlist->core.nr_mmaps; i++) {
		struct mmap *md = &evlist->mmap[i];

		if (md->core.cpu == cpu)
			return md;
	}

	return NULL;
}
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
struct TYPE_4__ {scalar_t__ threads; TYPE_1__* cpus; } ;
struct evlist {TYPE_2__ core; } ;
struct auxtrace_mmap_params {int idx; int cpu; int tid; } ;
struct TYPE_3__ {int* map; } ;

/* Variables and functions */
 void* perf_thread_map__pid (scalar_t__,int) ; 

void auxtrace_mmap_params__set_idx(struct auxtrace_mmap_params *mp,
				   struct evlist *evlist, int idx,
				   bool per_cpu)
{
	mp->idx = idx;

	if (per_cpu) {
		mp->cpu = evlist->core.cpus->map[idx];
		if (evlist->core.threads)
			mp->tid = perf_thread_map__pid(evlist->core.threads, 0);
		else
			mp->tid = -1;
	} else {
		mp->cpu = -1;
		mp->tid = perf_thread_map__pid(evlist->core.threads, idx);
	}
}
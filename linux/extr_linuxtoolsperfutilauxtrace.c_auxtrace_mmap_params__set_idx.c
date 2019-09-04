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
struct perf_evlist {scalar_t__ threads; TYPE_1__* cpus; } ;
struct auxtrace_mmap_params {int idx; int cpu; int tid; } ;
struct TYPE_2__ {int* map; } ;

/* Variables and functions */
 void* thread_map__pid (scalar_t__,int) ; 

void auxtrace_mmap_params__set_idx(struct auxtrace_mmap_params *mp,
				   struct perf_evlist *evlist, int idx,
				   bool per_cpu)
{
	mp->idx = idx;

	if (per_cpu) {
		mp->cpu = evlist->cpus->map[idx];
		if (evlist->threads)
			mp->tid = thread_map__pid(evlist->threads, 0);
		else
			mp->tid = -1;
	} else {
		mp->cpu = -1;
		mp->tid = thread_map__pid(evlist->threads, idx);
	}
}
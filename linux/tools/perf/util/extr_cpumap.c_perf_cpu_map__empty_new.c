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
struct perf_cpu_map {int nr; int* map; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 struct perf_cpu_map* malloc (int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct perf_cpu_map *perf_cpu_map__empty_new(int nr)
{
	struct perf_cpu_map *cpus = malloc(sizeof(*cpus) + sizeof(int) * nr);

	if (cpus != NULL) {
		int i;

		cpus->nr = nr;
		for (i = 0; i < nr; i++)
			cpus->map[i] = -1;

		refcount_set(&cpus->refcnt, 1);
	}

	return cpus;
}
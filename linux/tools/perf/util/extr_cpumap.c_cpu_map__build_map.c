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
 struct perf_cpu_map* calloc (int,int) ; 
 int /*<<< orphan*/  cmp_ids ; 
 int /*<<< orphan*/  qsort (int*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

int cpu_map__build_map(struct perf_cpu_map *cpus, struct perf_cpu_map **res,
		       int (*f)(struct perf_cpu_map *map, int cpu, void *data),
		       void *data)
{
	struct perf_cpu_map *c;
	int nr = cpus->nr;
	int cpu, s1, s2;

	/* allocate as much as possible */
	c = calloc(1, sizeof(*c) + nr * sizeof(int));
	if (!c)
		return -1;

	for (cpu = 0; cpu < nr; cpu++) {
		s1 = f(cpus, cpu, data);
		for (s2 = 0; s2 < c->nr; s2++) {
			if (s1 == c->map[s2])
				break;
		}
		if (s2 == c->nr) {
			c->map[c->nr] = s1;
			c->nr++;
		}
	}
	/* ensure we process id in increasing order */
	qsort(c->map, c->nr, sizeof(int), cmp_ids);

	refcount_set(&c->refcnt, 1);
	*res = c;
	return 0;
}
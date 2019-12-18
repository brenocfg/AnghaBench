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
struct perf_cpu_map {int nr; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 struct perf_cpu_map* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct perf_cpu_map *cpu_map__trim_new(int nr_cpus, int *tmp_cpus)
{
	size_t payload_size = nr_cpus * sizeof(int);
	struct perf_cpu_map *cpus = malloc(sizeof(*cpus) + payload_size);

	if (cpus != NULL) {
		cpus->nr = nr_cpus;
		memcpy(cpus->map, tmp_cpus, payload_size);
		refcount_set(&cpus->refcnt, 1);
	}

	return cpus;
}
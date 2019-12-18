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
typedef  scalar_t__ u16 ;
struct perf_cpu_map {int* map; } ;
struct cpu_map_entries {unsigned int nr; scalar_t__* cpu; } ;

/* Variables and functions */
 struct perf_cpu_map* perf_cpu_map__empty_new (unsigned int) ; 

__attribute__((used)) static struct perf_cpu_map *cpu_map__from_entries(struct cpu_map_entries *cpus)
{
	struct perf_cpu_map *map;

	map = perf_cpu_map__empty_new(cpus->nr);
	if (map) {
		unsigned i;

		for (i = 0; i < cpus->nr; i++) {
			/*
			 * Special treatment for -1, which is not real cpu number,
			 * and we need to use (int) -1 to initialize map[i],
			 * otherwise it would become 65535.
			 */
			if (cpus->cpu[i] == (u16) -1)
				map->map[i] = -1;
			else
				map->map[i] = (int) cpus->cpu[i];
		}
	}

	return map;
}
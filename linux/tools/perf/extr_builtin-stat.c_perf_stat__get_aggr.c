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
struct perf_stat_config {TYPE_1__* cpus_aggr_map; } ;
struct perf_cpu_map {int nr; int* map; } ;
typedef  int (* aggr_get_id_t ) (struct perf_stat_config*,struct perf_cpu_map*,int) ;
struct TYPE_2__ {int* map; } ;

/* Variables and functions */

__attribute__((used)) static int perf_stat__get_aggr(struct perf_stat_config *config,
			       aggr_get_id_t get_id, struct perf_cpu_map *map, int idx)
{
	int cpu;

	if (idx >= map->nr)
		return -1;

	cpu = map->map[idx];

	if (config->cpus_aggr_map->map[cpu] == -1)
		config->cpus_aggr_map->map[cpu] = get_id(config, map, idx);

	return config->cpus_aggr_map->map[cpu];
}
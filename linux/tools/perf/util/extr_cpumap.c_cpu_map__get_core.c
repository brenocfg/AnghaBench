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
struct perf_cpu_map {int nr; int* map; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int cpu_map__get_core_id (int) ; 
 int cpu_map__get_die (struct perf_cpu_map*,int,void*) ; 

int cpu_map__get_core(struct perf_cpu_map *map, int idx, void *data)
{
	int cpu, s_die;

	if (idx > map->nr)
		return -1;

	cpu = map->map[idx];

	cpu = cpu_map__get_core_id(cpu);

	/* s_die is the combination of socket + die id */
	s_die = cpu_map__get_die(map, idx, data);
	if (s_die == -1)
		return -1;

	/*
	 * encode socket in bit range 31:24
	 * encode die id in bit range 23:16
	 * core_id is relative to socket and die,
	 * we need a global id. So we combine
	 * socket + die id + core id
	 */
	if (WARN_ONCE(cpu >> 16, "The core id number is too big.\n"))
		return -1;

	return (s_die << 16) | (cpu & 0xffff);
}
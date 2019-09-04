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
struct cpu_map {int nr; int* map; } ;

/* Variables and functions */
 int cpu_map__get_core_id (int) ; 
 int cpu_map__get_socket (struct cpu_map*,int,void*) ; 

int cpu_map__get_core(struct cpu_map *map, int idx, void *data)
{
	int cpu, s;

	if (idx > map->nr)
		return -1;

	cpu = map->map[idx];

	cpu = cpu_map__get_core_id(cpu);

	s = cpu_map__get_socket(map, idx, data);
	if (s == -1)
		return -1;

	/*
	 * encode socket in upper 16 bits
	 * core_id is relative to socket, and
	 * we need a global id. So we combine
	 * socket+ core id
	 */
	return (s << 16) | (cpu & 0xffff);
}
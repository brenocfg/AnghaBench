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
 int cpu_map__get_die_id (int) ; 
 int cpu_map__get_socket (struct perf_cpu_map*,int,void*) ; 

int cpu_map__get_die(struct perf_cpu_map *map, int idx, void *data)
{
	int cpu, die_id, s;

	if (idx > map->nr)
		return -1;

	cpu = map->map[idx];

	die_id = cpu_map__get_die_id(cpu);
	/* There is no die_id on legacy system. */
	if (die_id == -1)
		die_id = 0;

	s = cpu_map__get_socket(map, idx, data);
	if (s == -1)
		return -1;

	/*
	 * Encode socket in bit range 15:8
	 * die_id is relative to socket, and
	 * we need a global id. So we combine
	 * socket + die id
	 */
	if (WARN_ONCE(die_id >> 8, "The die id number is too big.\n"))
		return -1;

	if (WARN_ONCE(s >> 8, "The socket id number is too big.\n"))
		return -1;

	return (s << 8) | (die_id & 0xff);
}
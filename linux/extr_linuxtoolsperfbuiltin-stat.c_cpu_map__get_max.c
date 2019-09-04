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

__attribute__((used)) static int cpu_map__get_max(struct cpu_map *map)
{
	int i, max = -1;

	for (i = 0; i < map->nr; i++) {
		if (map->map[i] > max)
			max = map->map[i];
	}

	return max;
}
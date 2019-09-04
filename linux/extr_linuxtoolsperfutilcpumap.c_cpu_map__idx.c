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

int cpu_map__idx(struct cpu_map *cpus, int cpu)
{
	int i;

	for (i = 0; i < cpus->nr; ++i) {
		if (cpus->map[i] == cpu)
			return i;
	}

	return -1;
}
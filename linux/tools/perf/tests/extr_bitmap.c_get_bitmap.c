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
struct perf_cpu_map {int nr; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 unsigned long* bitmap_alloc (int) ; 
 struct perf_cpu_map* perf_cpu_map__new (char const*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static unsigned long *get_bitmap(const char *str, int nbits)
{
	struct perf_cpu_map *map = perf_cpu_map__new(str);
	unsigned long *bm = NULL;
	int i;

	bm = bitmap_alloc(nbits);

	if (map && bm) {
		for (i = 0; i < map->nr; i++)
			set_bit(map->map[i], bm);
	}

	if (map)
		perf_cpu_map__put(map);
	return bm;
}
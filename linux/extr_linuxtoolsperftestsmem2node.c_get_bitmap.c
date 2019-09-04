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
struct cpu_map {int nr; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 unsigned long* bitmap_alloc (int) ; 
 struct cpu_map* cpu_map__new (char const*) ; 
 int /*<<< orphan*/  cpu_map__put (struct cpu_map*) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static unsigned long *get_bitmap(const char *str, int nbits)
{
	struct cpu_map *map = cpu_map__new(str);
	unsigned long *bm = NULL;
	int i;

	bm = bitmap_alloc(nbits);

	if (map && bm) {
		for (i = 0; i < map->nr; i++) {
			set_bit(map->map[i], bm);
		}
	}

	if (map)
		cpu_map__put(map);
	else
		free(bm);

	return bm && map ? bm : NULL;
}
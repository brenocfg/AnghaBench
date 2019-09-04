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
struct tracing_map {unsigned int max_elts; int /*<<< orphan*/  elts; int /*<<< orphan*/  map; int /*<<< orphan*/  drops; int /*<<< orphan*/  hits; int /*<<< orphan*/  next_elt; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TRACING_MAP_ELT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tracing_map_array_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracing_map_elt_clear (int /*<<< orphan*/ ) ; 

void tracing_map_clear(struct tracing_map *map)
{
	unsigned int i;

	atomic_set(&map->next_elt, -1);
	atomic64_set(&map->hits, 0);
	atomic64_set(&map->drops, 0);

	tracing_map_array_clear(map->map);

	for (i = 0; i < map->max_elts; i++)
		tracing_map_elt_clear(*(TRACING_MAP_ELT(map->elts, i)));
}
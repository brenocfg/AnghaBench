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
struct tracing_map {unsigned int max_elts; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** TRACING_MAP_ELT (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tracing_map_array_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracing_map_elt_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tracing_map_free_elts(struct tracing_map *map)
{
	unsigned int i;

	if (!map->elts)
		return;

	for (i = 0; i < map->max_elts; i++) {
		tracing_map_elt_free(*(TRACING_MAP_ELT(map->elts, i)));
		*(TRACING_MAP_ELT(map->elts, i)) = NULL;
	}

	tracing_map_array_free(map->elts);
	map->elts = NULL;
}
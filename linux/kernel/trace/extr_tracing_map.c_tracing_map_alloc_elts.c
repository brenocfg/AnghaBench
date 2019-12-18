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
struct tracing_map_elt {int dummy; } ;
struct tracing_map {unsigned int max_elts; int /*<<< orphan*/  elts; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** TRACING_MAP_ELT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tracing_map_array_alloc (unsigned int,int) ; 
 int /*<<< orphan*/ * tracing_map_elt_alloc (struct tracing_map*) ; 
 int /*<<< orphan*/  tracing_map_free_elts (struct tracing_map*) ; 

__attribute__((used)) static int tracing_map_alloc_elts(struct tracing_map *map)
{
	unsigned int i;

	map->elts = tracing_map_array_alloc(map->max_elts,
					    sizeof(struct tracing_map_elt *));
	if (!map->elts)
		return -ENOMEM;

	for (i = 0; i < map->max_elts; i++) {
		*(TRACING_MAP_ELT(map->elts, i)) = tracing_map_elt_alloc(map);
		if (IS_ERR(*(TRACING_MAP_ELT(map->elts, i)))) {
			*(TRACING_MAP_ELT(map->elts, i)) = NULL;
			tracing_map_free_elts(map);

			return -ENOMEM;
		}
	}

	return 0;
}
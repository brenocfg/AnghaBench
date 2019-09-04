#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tracing_map_elt {int dummy; } ;
struct tracing_map {int max_elts; TYPE_1__* ops; int /*<<< orphan*/  elts; int /*<<< orphan*/  next_elt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* elt_init ) (struct tracing_map_elt*) ;} ;

/* Variables and functions */
 struct tracing_map_elt** TRACING_MAP_ELT (int /*<<< orphan*/ ,int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tracing_map_elt*) ; 

__attribute__((used)) static struct tracing_map_elt *get_free_elt(struct tracing_map *map)
{
	struct tracing_map_elt *elt = NULL;
	int idx;

	idx = atomic_inc_return(&map->next_elt);
	if (idx < map->max_elts) {
		elt = *(TRACING_MAP_ELT(map->elts, idx));
		if (map->ops && map->ops->elt_init)
			map->ops->elt_init(elt);
	}

	return elt;
}
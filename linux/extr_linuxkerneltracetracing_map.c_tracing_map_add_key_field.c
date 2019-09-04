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
typedef  int /*<<< orphan*/  tracing_map_cmp_fn_t ;
struct tracing_map {int* key_idx; int /*<<< orphan*/  n_keys; TYPE_1__* fields; } ;
struct TYPE_2__ {unsigned int offset; } ;

/* Variables and functions */
 int tracing_map_add_field (struct tracing_map*,int /*<<< orphan*/ ) ; 

int tracing_map_add_key_field(struct tracing_map *map,
			      unsigned int offset,
			      tracing_map_cmp_fn_t cmp_fn)

{
	int idx = tracing_map_add_field(map, cmp_fn);

	if (idx < 0)
		return idx;

	map->fields[idx].offset = offset;

	map->key_idx[map->n_keys++] = idx;

	return idx;
}
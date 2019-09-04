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
struct tracing_map {int n_fields; TYPE_1__* fields; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmp_fn; } ;

/* Variables and functions */
 int EINVAL ; 
 int TRACING_MAP_FIELDS_MAX ; 

__attribute__((used)) static int tracing_map_add_field(struct tracing_map *map,
				 tracing_map_cmp_fn_t cmp_fn)
{
	int ret = -EINVAL;

	if (map->n_fields < TRACING_MAP_FIELDS_MAX) {
		ret = map->n_fields;
		map->fields[map->n_fields++].cmp_fn = cmp_fn;
	}

	return ret;
}
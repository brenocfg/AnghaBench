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
struct tracing_map {scalar_t__ n_vars; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TRACING_MAP_VARS_MAX ; 

int tracing_map_add_var(struct tracing_map *map)
{
	int ret = -EINVAL;

	if (map->n_vars < TRACING_MAP_VARS_MAX)
		ret = map->n_vars++;

	return ret;
}
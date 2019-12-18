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
struct tracing_map {int n_fields; } ;

/* Variables and functions */
 int EINVAL ; 
 int tracing_map_alloc_elts (struct tracing_map*) ; 
 int /*<<< orphan*/  tracing_map_clear (struct tracing_map*) ; 

int tracing_map_init(struct tracing_map *map)
{
	int err;

	if (map->n_fields < 2)
		return -EINVAL; /* need at least 1 key and 1 val */

	err = tracing_map_alloc_elts(map);
	if (err)
		return err;

	tracing_map_clear(map);

	return err;
}
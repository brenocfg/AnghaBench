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
struct tracing_map {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tracing_map*) ; 
 int /*<<< orphan*/  tracing_map_array_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracing_map_free_elts (struct tracing_map*) ; 

void tracing_map_destroy(struct tracing_map *map)
{
	if (!map)
		return;

	tracing_map_free_elts(map);

	tracing_map_array_free(map->map);
	kfree(map);
}
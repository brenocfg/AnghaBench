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
struct tracing_map {unsigned int n_keys; unsigned int* key_idx; } ;

/* Variables and functions */

__attribute__((used)) static bool is_key(struct tracing_map *map, unsigned int field_idx)
{
	unsigned int i;

	for (i = 0; i < map->n_keys; i++)
		if (map->key_idx[i] == field_idx)
			return true;
	return false;
}
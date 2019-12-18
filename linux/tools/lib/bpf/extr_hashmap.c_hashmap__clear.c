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
struct hashmap {scalar_t__ sz; scalar_t__ cap_bits; scalar_t__ cap; int /*<<< orphan*/  buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void hashmap__clear(struct hashmap *map)
{
	free(map->buckets);
	map->cap = map->cap_bits = map->sz = 0;
}
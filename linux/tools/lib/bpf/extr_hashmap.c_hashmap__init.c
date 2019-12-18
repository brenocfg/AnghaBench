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
struct hashmap {scalar_t__ sz; scalar_t__ cap_bits; scalar_t__ cap; int /*<<< orphan*/ * buckets; void* ctx; int /*<<< orphan*/  equal_fn; int /*<<< orphan*/  hash_fn; } ;
typedef  int /*<<< orphan*/  hashmap_hash_fn ;
typedef  int /*<<< orphan*/  hashmap_equal_fn ;

/* Variables and functions */

void hashmap__init(struct hashmap *map, hashmap_hash_fn hash_fn,
		   hashmap_equal_fn equal_fn, void *ctx)
{
	map->hash_fn = hash_fn;
	map->equal_fn = equal_fn;
	map->ctx = ctx;

	map->buckets = NULL;
	map->cap = 0;
	map->cap_bits = 0;
	map->sz = 0;
}
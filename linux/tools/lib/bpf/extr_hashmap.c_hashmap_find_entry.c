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
struct hashmap_entry {int /*<<< orphan*/  key; struct hashmap_entry* next; } ;
struct hashmap {int /*<<< orphan*/  ctx; scalar_t__ (* equal_fn ) (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ;struct hashmap_entry** buckets; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hashmap_find_entry(const struct hashmap *map,
			       const void *key, size_t hash,
			       struct hashmap_entry ***pprev,
			       struct hashmap_entry **entry)
{
	struct hashmap_entry *cur, **prev_ptr;

	if (!map->buckets)
		return false;

	for (prev_ptr = &map->buckets[hash], cur = *prev_ptr;
	     cur;
	     prev_ptr = &cur->next, cur = cur->next) {
		if (map->equal_fn(cur->key, key, map->ctx)) {
			if (pprev)
				*pprev = prev_ptr;
			*entry = cur;
			return true;
		}
	}

	return false;
}
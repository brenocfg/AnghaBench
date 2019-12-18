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
typedef  int u32 ;
struct tracing_map_entry {int key; struct tracing_map_elt* val; } ;
struct tracing_map_elt {int /*<<< orphan*/  key; } ;
struct tracing_map {int map_bits; int map_size; int /*<<< orphan*/  hits; int /*<<< orphan*/  key_size; int /*<<< orphan*/  drops; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 struct tracing_map_elt* READ_ONCE (struct tracing_map_elt*) ; 
 struct tracing_map_entry* TRACING_MAP_ENTRY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpxchg (int*,int /*<<< orphan*/ ,int) ; 
 struct tracing_map_elt* get_free_elt (struct tracing_map*) ; 
 int jhash (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ keys_match (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct tracing_map_elt *
__tracing_map_insert(struct tracing_map *map, void *key, bool lookup_only)
{
	u32 idx, key_hash, test_key;
	int dup_try = 0;
	struct tracing_map_entry *entry;
	struct tracing_map_elt *val;

	key_hash = jhash(key, map->key_size, 0);
	if (key_hash == 0)
		key_hash = 1;
	idx = key_hash >> (32 - (map->map_bits + 1));

	while (1) {
		idx &= (map->map_size - 1);
		entry = TRACING_MAP_ENTRY(map->map, idx);
		test_key = entry->key;

		if (test_key && test_key == key_hash) {
			val = READ_ONCE(entry->val);
			if (val &&
			    keys_match(key, val->key, map->key_size)) {
				if (!lookup_only)
					atomic64_inc(&map->hits);
				return val;
			} else if (unlikely(!val)) {
				/*
				 * The key is present. But, val (pointer to elt
				 * struct) is still NULL. which means some other
				 * thread is in the process of inserting an
				 * element.
				 *
				 * On top of that, it's key_hash is same as the
				 * one being inserted right now. So, it's
				 * possible that the element has the same
				 * key as well.
				 */

				dup_try++;
				if (dup_try > map->map_size) {
					atomic64_inc(&map->drops);
					break;
				}
				continue;
			}
		}

		if (!test_key) {
			if (lookup_only)
				break;

			if (!cmpxchg(&entry->key, 0, key_hash)) {
				struct tracing_map_elt *elt;

				elt = get_free_elt(map);
				if (!elt) {
					atomic64_inc(&map->drops);
					entry->key = 0;
					break;
				}

				memcpy(elt->key, key, map->key_size);
				entry->val = elt;
				atomic64_inc(&map->hits);

				return entry->val;
			} else {
				/*
				 * cmpxchg() failed. Loop around once
				 * more to check what key was inserted.
				 */
				dup_try++;
				continue;
			}
		}

		idx++;
	}

	return NULL;
}
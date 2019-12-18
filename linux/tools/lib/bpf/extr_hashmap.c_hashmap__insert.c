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
struct hashmap_entry {void* key; void* value; } ;
struct hashmap {int /*<<< orphan*/  sz; int /*<<< orphan*/ * buckets; int /*<<< orphan*/  cap_bits; int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* hash_fn ) (void const*,int /*<<< orphan*/ ) ;} ;
typedef  enum hashmap_insert_strategy { ____Placeholder_hashmap_insert_strategy } hashmap_insert_strategy ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int HASHMAP_ADD ; 
 int HASHMAP_APPEND ; 
 int HASHMAP_SET ; 
 int HASHMAP_UPDATE ; 
 size_t hash_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_add_entry (int /*<<< orphan*/ *,struct hashmap_entry*) ; 
 scalar_t__ hashmap_find_entry (struct hashmap*,void const*,size_t,int /*<<< orphan*/ *,struct hashmap_entry**) ; 
 int hashmap_grow (struct hashmap*) ; 
 scalar_t__ hashmap_needs_to_grow (struct hashmap*) ; 
 struct hashmap_entry* malloc (int) ; 
 int /*<<< orphan*/  stub1 (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void const*,int /*<<< orphan*/ ) ; 

int hashmap__insert(struct hashmap *map, const void *key, void *value,
		    enum hashmap_insert_strategy strategy,
		    const void **old_key, void **old_value)
{
	struct hashmap_entry *entry;
	size_t h;
	int err;

	if (old_key)
		*old_key = NULL;
	if (old_value)
		*old_value = NULL;

	h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	if (strategy != HASHMAP_APPEND &&
	    hashmap_find_entry(map, key, h, NULL, &entry)) {
		if (old_key)
			*old_key = entry->key;
		if (old_value)
			*old_value = entry->value;

		if (strategy == HASHMAP_SET || strategy == HASHMAP_UPDATE) {
			entry->key = key;
			entry->value = value;
			return 0;
		} else if (strategy == HASHMAP_ADD) {
			return -EEXIST;
		}
	}

	if (strategy == HASHMAP_UPDATE)
		return -ENOENT;

	if (hashmap_needs_to_grow(map)) {
		err = hashmap_grow(map);
		if (err)
			return err;
		h = hash_bits(map->hash_fn(key, map->ctx), map->cap_bits);
	}

	entry = malloc(sizeof(struct hashmap_entry));
	if (!entry)
		return -ENOMEM;

	entry->key = key;
	entry->value = value;
	hashmap_add_entry(&map->buckets[h], entry);
	map->sz++;

	return 0;
}
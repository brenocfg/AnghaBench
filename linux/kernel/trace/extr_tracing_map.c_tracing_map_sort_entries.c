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
struct tracing_map_sort_key {int /*<<< orphan*/  field_idx; } ;
struct tracing_map_sort_entry {int dummy; } ;
struct tracing_map_entry {TYPE_1__* val; int /*<<< orphan*/  key; } ;
struct tracing_map {int map_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  map; int /*<<< orphan*/  max_elts; } ;
typedef  int /*<<< orphan*/  sort_entry ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tracing_map_entry* TRACING_MAP_ENTRY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  array_size (int,int /*<<< orphan*/ ) ; 
 int cmp_entries_key (struct tracing_map_sort_entry const**,struct tracing_map_sort_entry const**) ; 
 int cmp_entries_sum (struct tracing_map_sort_entry const**,struct tracing_map_sort_entry const**) ; 
 struct tracing_map_sort_entry* create_sort_entry (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  detect_dups (struct tracing_map_sort_entry**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_key (struct tracing_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sort_key (struct tracing_map*,struct tracing_map_sort_key*) ; 
 int /*<<< orphan*/  sort (struct tracing_map_sort_entry**,int,int,int (*) (void const*,void const*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_secondary (struct tracing_map*,struct tracing_map_sort_entry const**,int,struct tracing_map_sort_key*,struct tracing_map_sort_key*) ; 
 int /*<<< orphan*/  tracing_map_destroy_sort_entries (struct tracing_map_sort_entry**,int) ; 
 struct tracing_map_sort_entry** vmalloc (int /*<<< orphan*/ ) ; 

int tracing_map_sort_entries(struct tracing_map *map,
			     struct tracing_map_sort_key *sort_keys,
			     unsigned int n_sort_keys,
			     struct tracing_map_sort_entry ***sort_entries)
{
	int (*cmp_entries_fn)(const struct tracing_map_sort_entry **,
			      const struct tracing_map_sort_entry **);
	struct tracing_map_sort_entry *sort_entry, **entries;
	int i, n_entries, ret;

	entries = vmalloc(array_size(sizeof(sort_entry), map->max_elts));
	if (!entries)
		return -ENOMEM;

	for (i = 0, n_entries = 0; i < map->map_size; i++) {
		struct tracing_map_entry *entry;

		entry = TRACING_MAP_ENTRY(map->map, i);

		if (!entry->key || !entry->val)
			continue;

		entries[n_entries] = create_sort_entry(entry->val->key,
						       entry->val);
		if (!entries[n_entries++]) {
			ret = -ENOMEM;
			goto free;
		}
	}

	if (n_entries == 0) {
		ret = 0;
		goto free;
	}

	if (n_entries == 1) {
		*sort_entries = entries;
		return 1;
	}

	detect_dups(entries, n_entries, map->key_size);

	if (is_key(map, sort_keys[0].field_idx))
		cmp_entries_fn = cmp_entries_key;
	else
		cmp_entries_fn = cmp_entries_sum;

	set_sort_key(map, &sort_keys[0]);

	sort(entries, n_entries, sizeof(struct tracing_map_sort_entry *),
	     (int (*)(const void *, const void *))cmp_entries_fn, NULL);

	if (n_sort_keys > 1)
		sort_secondary(map,
			       (const struct tracing_map_sort_entry **)entries,
			       n_entries,
			       &sort_keys[0],
			       &sort_keys[1]);

	*sort_entries = entries;

	return n_entries;
 free:
	tracing_map_destroy_sort_entries(entries, n_entries);

	return ret;
}
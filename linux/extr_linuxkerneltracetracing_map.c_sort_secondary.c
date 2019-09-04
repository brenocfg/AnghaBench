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
struct tracing_map_sort_key {int /*<<< orphan*/  field_idx; } ;
struct tracing_map_sort_entry {int dummy; } ;
struct tracing_map {int dummy; } ;

/* Variables and functions */
 int cmp_entries_key (struct tracing_map_sort_entry const**,struct tracing_map_sort_entry const**) ; 
 int cmp_entries_sum (struct tracing_map_sort_entry const**,struct tracing_map_sort_entry const**) ; 
 scalar_t__ is_key (struct tracing_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sort_key (struct tracing_map*,struct tracing_map_sort_key*) ; 
 int /*<<< orphan*/  sort (struct tracing_map_sort_entry const**,unsigned int,int,int (*) (void const*,void const*),int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sort_secondary(struct tracing_map *map,
			   const struct tracing_map_sort_entry **entries,
			   unsigned int n_entries,
			   struct tracing_map_sort_key *primary_key,
			   struct tracing_map_sort_key *secondary_key)
{
	int (*primary_fn)(const struct tracing_map_sort_entry **,
			  const struct tracing_map_sort_entry **);
	int (*secondary_fn)(const struct tracing_map_sort_entry **,
			    const struct tracing_map_sort_entry **);
	unsigned i, start = 0, n_sub = 1;

	if (is_key(map, primary_key->field_idx))
		primary_fn = cmp_entries_key;
	else
		primary_fn = cmp_entries_sum;

	if (is_key(map, secondary_key->field_idx))
		secondary_fn = cmp_entries_key;
	else
		secondary_fn = cmp_entries_sum;

	for (i = 0; i < n_entries - 1; i++) {
		const struct tracing_map_sort_entry **a = &entries[i];
		const struct tracing_map_sort_entry **b = &entries[i + 1];

		if (primary_fn(a, b) == 0) {
			n_sub++;
			if (i < n_entries - 2)
				continue;
		}

		if (n_sub < 2) {
			start = i + 1;
			n_sub = 1;
			continue;
		}

		set_sort_key(map, secondary_key);
		sort(&entries[start], n_sub,
		     sizeof(struct tracing_map_sort_entry *),
		     (int (*)(const void *, const void *))secondary_fn, NULL);
		set_sort_key(map, primary_key);

		start = i + 1;
		n_sub = 1;
	}
}
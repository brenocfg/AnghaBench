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
typedef  int (* tracing_map_cmp_fn_t ) (void*,void*) ;
struct tracing_map_sort_key {size_t field_idx; scalar_t__ descending; } ;
struct tracing_map_sort_entry {struct tracing_map_elt* elt; } ;
struct tracing_map_field {int (* cmp_fn ) (void*,void*) ;int offset; } ;
struct tracing_map_elt {void* key; struct tracing_map_field* fields; TYPE_1__* map; } ;
struct TYPE_2__ {struct tracing_map_sort_key sort_key; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_entries_key(const struct tracing_map_sort_entry **a,
			   const struct tracing_map_sort_entry **b)
{
	const struct tracing_map_elt *elt_a, *elt_b;
	struct tracing_map_sort_key *sort_key;
	struct tracing_map_field *field;
	tracing_map_cmp_fn_t cmp_fn;
	void *val_a, *val_b;
	int ret = 0;

	elt_a = (*a)->elt;
	elt_b = (*b)->elt;

	sort_key = &elt_a->map->sort_key;

	field = &elt_a->fields[sort_key->field_idx];

	cmp_fn = field->cmp_fn;

	val_a = elt_a->key + field->offset;
	val_b = elt_b->key + field->offset;

	ret = cmp_fn(val_a, val_b);
	if (sort_key->descending)
		ret = -ret;

	return ret;
}
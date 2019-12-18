#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tracing_map_elt {TYPE_2__* map; TYPE_3__* fields; } ;
struct TYPE_6__ {scalar_t__ cmp_fn; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {unsigned int n_fields; TYPE_1__* fields; } ;
struct TYPE_4__ {scalar_t__ cmp_fn; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ tracing_map_cmp_atomic64 ; 
 int /*<<< orphan*/  tracing_map_elt_clear (struct tracing_map_elt*) ; 

__attribute__((used)) static void tracing_map_elt_init_fields(struct tracing_map_elt *elt)
{
	unsigned int i;

	tracing_map_elt_clear(elt);

	for (i = 0; i < elt->map->n_fields; i++) {
		elt->fields[i].cmp_fn = elt->map->fields[i].cmp_fn;

		if (elt->fields[i].cmp_fn != tracing_map_cmp_atomic64)
			elt->fields[i].offset = elt->map->fields[i].offset;
	}
}
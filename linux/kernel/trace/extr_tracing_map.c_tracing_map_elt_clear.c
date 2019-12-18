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
struct tracing_map_elt {int* var_set; TYPE_3__* map; int /*<<< orphan*/ * vars; TYPE_1__* fields; } ;
struct TYPE_6__ {unsigned int n_fields; unsigned int n_vars; TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* elt_clear ) (struct tracing_map_elt*) ;} ;
struct TYPE_4__ {scalar_t__ cmp_fn; int /*<<< orphan*/  sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tracing_map_elt*) ; 
 scalar_t__ tracing_map_cmp_atomic64 ; 

__attribute__((used)) static void tracing_map_elt_clear(struct tracing_map_elt *elt)
{
	unsigned i;

	for (i = 0; i < elt->map->n_fields; i++)
		if (elt->fields[i].cmp_fn == tracing_map_cmp_atomic64)
			atomic64_set(&elt->fields[i].sum, 0);

	for (i = 0; i < elt->map->n_vars; i++) {
		atomic64_set(&elt->vars[i], 0);
		elt->var_set[i] = false;
	}

	if (elt->map->ops && elt->map->ops->elt_clear)
		elt->map->ops->elt_clear(elt);
}
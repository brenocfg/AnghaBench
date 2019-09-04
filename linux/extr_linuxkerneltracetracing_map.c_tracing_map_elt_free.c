#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tracing_map_elt {struct tracing_map_elt* key; struct tracing_map_elt* var_set; struct tracing_map_elt* vars; struct tracing_map_elt* fields; TYPE_2__* map; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* elt_free ) (struct tracing_map_elt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tracing_map_elt*) ; 
 int /*<<< orphan*/  stub1 (struct tracing_map_elt*) ; 

__attribute__((used)) static void tracing_map_elt_free(struct tracing_map_elt *elt)
{
	if (!elt)
		return;

	if (elt->map->ops && elt->map->ops->elt_free)
		elt->map->ops->elt_free(elt);
	kfree(elt->fields);
	kfree(elt->vars);
	kfree(elt->var_set);
	kfree(elt->key);
	kfree(elt);
}
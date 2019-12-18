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
struct objagg {scalar_t__ hints; int /*<<< orphan*/  obj_ht; int /*<<< orphan*/  obj_list; int /*<<< orphan*/  root_ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct objagg*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objagg_hints_put (scalar_t__) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_objagg_destroy (struct objagg*) ; 

void objagg_destroy(struct objagg *objagg)
{
	trace_objagg_destroy(objagg);
	ida_destroy(&objagg->root_ida);
	WARN_ON(!list_empty(&objagg->obj_list));
	rhashtable_destroy(&objagg->obj_ht);
	if (objagg->hints)
		objagg_hints_put(objagg->hints);
	kfree(objagg);
}
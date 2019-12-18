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
struct objagg_obj {int /*<<< orphan*/  ht_node; int /*<<< orphan*/  list; } ;
struct objagg {int /*<<< orphan*/  ht_params; int /*<<< orphan*/  obj_ht; int /*<<< orphan*/  obj_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct objagg_obj*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objagg_obj_fini (struct objagg*,struct objagg_obj*) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_objagg_obj_destroy (struct objagg*,struct objagg_obj*) ; 

__attribute__((used)) static void objagg_obj_destroy(struct objagg *objagg,
			       struct objagg_obj *objagg_obj)
{
	trace_objagg_obj_destroy(objagg, objagg_obj);
	--objagg->obj_count;
	list_del(&objagg_obj->list);
	rhashtable_remove_fast(&objagg->obj_ht, &objagg_obj->ht_node,
			       objagg->ht_params);
	objagg_obj_fini(objagg, objagg_obj);
	kfree(objagg_obj);
}
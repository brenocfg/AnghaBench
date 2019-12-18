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
struct objagg_obj {int /*<<< orphan*/  list; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  obj; } ;
struct objagg {int /*<<< orphan*/  obj_count; int /*<<< orphan*/  obj_list; int /*<<< orphan*/  ht_params; int /*<<< orphan*/  obj_ht; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ obj_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct objagg_obj* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct objagg_obj*) ; 
 struct objagg_obj* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  objagg_obj_fini (struct objagg*,struct objagg_obj*) ; 
 int objagg_obj_init (struct objagg*,struct objagg_obj*) ; 
 int /*<<< orphan*/  objagg_obj_ref_inc (struct objagg_obj*) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_objagg_obj_create (struct objagg*,struct objagg_obj*) ; 

__attribute__((used)) static struct objagg_obj *objagg_obj_create(struct objagg *objagg, void *obj)
{
	struct objagg_obj *objagg_obj;
	int err;

	objagg_obj = kzalloc(sizeof(*objagg_obj) + objagg->ops->obj_size,
			     GFP_KERNEL);
	if (!objagg_obj)
		return ERR_PTR(-ENOMEM);
	objagg_obj_ref_inc(objagg_obj);
	memcpy(objagg_obj->obj, obj, objagg->ops->obj_size);

	err = objagg_obj_init(objagg, objagg_obj);
	if (err)
		goto err_obj_init;

	err = rhashtable_insert_fast(&objagg->obj_ht, &objagg_obj->ht_node,
				     objagg->ht_params);
	if (err)
		goto err_ht_insert;
	list_add(&objagg_obj->list, &objagg->obj_list);
	objagg->obj_count++;
	trace_objagg_obj_create(objagg, objagg_obj);

	return objagg_obj;

err_ht_insert:
	objagg_obj_fini(objagg, objagg_obj);
err_obj_init:
	kfree(objagg_obj);
	return ERR_PTR(err);
}
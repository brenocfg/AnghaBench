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
struct objagg_obj {int /*<<< orphan*/  refcount; struct objagg_obj* parent; void* delta_priv; int /*<<< orphan*/  obj; } ;
struct objagg {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {void* (* delta_create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  objagg_obj_ref_inc (struct objagg_obj*) ; 
 void* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_objagg_obj_parent_assign (struct objagg*,struct objagg_obj*,struct objagg_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int objagg_obj_parent_assign(struct objagg *objagg,
				    struct objagg_obj *objagg_obj,
				    struct objagg_obj *parent,
				    bool take_parent_ref)
{
	void *delta_priv;

	delta_priv = objagg->ops->delta_create(objagg->priv, parent->obj,
					       objagg_obj->obj);
	if (IS_ERR(delta_priv))
		return PTR_ERR(delta_priv);

	/* User returned a delta private, that means that
	 * our object can be aggregated into the parent.
	 */
	objagg_obj->parent = parent;
	objagg_obj->delta_priv = delta_priv;
	if (take_parent_ref)
		objagg_obj_ref_inc(objagg_obj->parent);
	trace_objagg_obj_parent_assign(objagg, objagg_obj,
				       parent,
				       parent->refcount);
	return 0;
}
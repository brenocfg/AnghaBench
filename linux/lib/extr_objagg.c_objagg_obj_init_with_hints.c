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
struct objagg_obj {int /*<<< orphan*/  obj; } ;
struct objagg_hints_node {TYPE_1__* parent; } ;
struct objagg {int /*<<< orphan*/  hints; } ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct objagg_obj*) ; 
 int PTR_ERR (struct objagg_obj*) ; 
 struct objagg_obj* __objagg_obj_get (struct objagg*,int /*<<< orphan*/ ) ; 
 struct objagg_hints_node* objagg_hints_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int objagg_obj_parent_assign (struct objagg*,struct objagg_obj*,struct objagg_obj*,int) ; 
 int /*<<< orphan*/  objagg_obj_put (struct objagg*,struct objagg_obj*) ; 
 int objagg_obj_root_create (struct objagg*,struct objagg_obj*,struct objagg_hints_node*) ; 

__attribute__((used)) static int objagg_obj_init_with_hints(struct objagg *objagg,
				      struct objagg_obj *objagg_obj,
				      bool *hint_found)
{
	struct objagg_hints_node *hnode;
	struct objagg_obj *parent;
	int err;

	hnode = objagg_hints_lookup(objagg->hints, objagg_obj->obj);
	if (!hnode) {
		*hint_found = false;
		return 0;
	}
	*hint_found = true;

	if (!hnode->parent)
		return objagg_obj_root_create(objagg, objagg_obj, hnode);

	parent = __objagg_obj_get(objagg, hnode->parent->obj);
	if (IS_ERR(parent))
		return PTR_ERR(parent);

	err = objagg_obj_parent_assign(objagg, objagg_obj, parent, false);
	if (err) {
		*hint_found = false;
		err = 0;
		goto err_parent_assign;
	}

	return 0;

err_parent_assign:
	objagg_obj_put(objagg, parent);
	return err;
}
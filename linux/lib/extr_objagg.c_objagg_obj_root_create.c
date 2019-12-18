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
struct objagg_obj {int /*<<< orphan*/  root_priv; int /*<<< orphan*/  root_id; int /*<<< orphan*/  obj; } ;
struct objagg_hints_node {int dummy; } ;
struct objagg {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* root_create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int objagg_obj_root_id_alloc (struct objagg*,struct objagg_obj*,struct objagg_hints_node*) ; 
 int /*<<< orphan*/  objagg_obj_root_id_free (struct objagg*,struct objagg_obj*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_objagg_obj_root_create (struct objagg*,struct objagg_obj*) ; 

__attribute__((used)) static int objagg_obj_root_create(struct objagg *objagg,
				  struct objagg_obj *objagg_obj,
				  struct objagg_hints_node *hnode)
{
	int err;

	err = objagg_obj_root_id_alloc(objagg, objagg_obj, hnode);
	if (err)
		return err;
	objagg_obj->root_priv = objagg->ops->root_create(objagg->priv,
							 objagg_obj->obj,
							 objagg_obj->root_id);
	if (IS_ERR(objagg_obj->root_priv)) {
		err = PTR_ERR(objagg_obj->root_priv);
		goto err_root_create;
	}
	trace_objagg_obj_root_create(objagg, objagg_obj);
	return 0;

err_root_create:
	objagg_obj_root_id_free(objagg, objagg_obj);
	return err;
}
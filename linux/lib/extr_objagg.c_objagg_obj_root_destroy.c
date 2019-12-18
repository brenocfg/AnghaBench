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
struct objagg_obj {int /*<<< orphan*/  root_priv; } ;
struct objagg {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* root_destroy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  objagg_obj_root_id_free (struct objagg*,struct objagg_obj*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_objagg_obj_root_destroy (struct objagg*,struct objagg_obj*) ; 

__attribute__((used)) static void objagg_obj_root_destroy(struct objagg *objagg,
				    struct objagg_obj *objagg_obj)
{
	trace_objagg_obj_root_destroy(objagg, objagg_obj);
	objagg->ops->root_destroy(objagg->priv, objagg_obj->root_priv);
	objagg_obj_root_id_free(objagg, objagg_obj);
}
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
struct objagg_obj {int dummy; } ;
struct objagg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  objagg_obj_is_root (struct objagg_obj*) ; 
 int /*<<< orphan*/  objagg_obj_parent_unassign (struct objagg*,struct objagg_obj*) ; 
 int /*<<< orphan*/  objagg_obj_root_destroy (struct objagg*,struct objagg_obj*) ; 

__attribute__((used)) static void objagg_obj_fini(struct objagg *objagg,
			    struct objagg_obj *objagg_obj)
{
	if (!objagg_obj_is_root(objagg_obj))
		objagg_obj_parent_unassign(objagg, objagg_obj);
	else
		objagg_obj_root_destroy(objagg, objagg_obj);
}
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
struct klp_object {struct klp_func* funcs; } ;
struct klp_func {int /*<<< orphan*/  kobj; scalar_t__ old_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void klp_free_funcs_limited(struct klp_object *obj,
				   struct klp_func *limit)
{
	struct klp_func *func;

	for (func = obj->funcs; func->old_name && func != limit; func++)
		kobject_put(&func->kobj);
}
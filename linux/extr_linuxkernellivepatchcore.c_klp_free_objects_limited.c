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
struct klp_patch {struct klp_object* objs; } ;
struct klp_object {int /*<<< orphan*/  kobj; scalar_t__ funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  klp_free_funcs_limited (struct klp_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void klp_free_objects_limited(struct klp_patch *patch,
				     struct klp_object *limit)
{
	struct klp_object *obj;

	for (obj = patch->objs; obj->funcs && obj != limit; obj++) {
		klp_free_funcs_limited(obj, NULL);
		kobject_put(&obj->kobj);
	}
}
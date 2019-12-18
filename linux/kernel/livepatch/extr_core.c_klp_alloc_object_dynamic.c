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
struct klp_patch {int dummy; } ;
struct klp_object {int dynamic; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct klp_object*) ; 
 int /*<<< orphan*/  klp_init_object_early (struct klp_patch*,struct klp_object*) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct klp_object* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct klp_object *klp_alloc_object_dynamic(const char *name,
						   struct klp_patch *patch)
{
	struct klp_object *obj;

	obj = kzalloc(sizeof(*obj), GFP_KERNEL);
	if (!obj)
		return NULL;

	if (name) {
		obj->name = kstrdup(name, GFP_KERNEL);
		if (!obj->name) {
			kfree(obj);
			return NULL;
		}
	}

	klp_init_object_early(patch, obj);
	obj->dynamic = true;

	return obj;
}
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
struct target {int /*<<< orphan*/  np; scalar_t__ in_livetree; } ;
struct property {struct property* value; struct property* name; } ;
struct overlay_changeset {int /*<<< orphan*/  cset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct property* __of_prop_dup (struct property*,int /*<<< orphan*/ ) ; 
 struct property* dup_and_fixup_symbol_prop (struct overlay_changeset*,struct property*) ; 
 int /*<<< orphan*/  kfree (struct property*) ; 
 int of_changeset_add_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct property*) ; 
 int of_changeset_update_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct property*) ; 
 struct property* of_find_property (int /*<<< orphan*/ ,struct property*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_prop_cmp (struct property*,char*) ; 

__attribute__((used)) static int add_changeset_property(struct overlay_changeset *ovcs,
		struct target *target, struct property *overlay_prop,
		bool is_symbols_prop)
{
	struct property *new_prop = NULL, *prop;
	int ret = 0;

	if (!of_prop_cmp(overlay_prop->name, "name") ||
	    !of_prop_cmp(overlay_prop->name, "phandle") ||
	    !of_prop_cmp(overlay_prop->name, "linux,phandle"))
		return 0;

	if (target->in_livetree)
		prop = of_find_property(target->np, overlay_prop->name, NULL);
	else
		prop = NULL;

	if (is_symbols_prop) {
		if (prop)
			return -EINVAL;
		new_prop = dup_and_fixup_symbol_prop(ovcs, overlay_prop);
	} else {
		new_prop = __of_prop_dup(overlay_prop, GFP_KERNEL);
	}

	if (!new_prop)
		return -ENOMEM;

	if (!prop)
		ret = of_changeset_add_property(&ovcs->cset, target->np,
						new_prop);
	else
		ret = of_changeset_update_property(&ovcs->cset, target->np,
						   new_prop);

	if (ret) {
		kfree(new_prop->name);
		kfree(new_prop->value);
		kfree(new_prop);
	}
	return ret;
}
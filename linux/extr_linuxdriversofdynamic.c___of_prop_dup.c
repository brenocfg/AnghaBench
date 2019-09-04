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
struct property {struct property* value; struct property* name; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_DYNAMIC ; 
 int /*<<< orphan*/  kfree (struct property*) ; 
 struct property* kmemdup (struct property*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct property* kstrdup (struct property*,int /*<<< orphan*/ ) ; 
 struct property* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_set_flag (struct property*,int /*<<< orphan*/ ) ; 

struct property *__of_prop_dup(const struct property *prop, gfp_t allocflags)
{
	struct property *new;

	new = kzalloc(sizeof(*new), allocflags);
	if (!new)
		return NULL;

	/*
	 * NOTE: There is no check for zero length value.
	 * In case of a boolean property, this will allocate a value
	 * of zero bytes. We do this to work around the use
	 * of of_get_property() calls on boolean values.
	 */
	new->name = kstrdup(prop->name, allocflags);
	new->value = kmemdup(prop->value, prop->length, allocflags);
	new->length = prop->length;
	if (!new->name || !new->value)
		goto err_free;

	/* mark the property as dynamic */
	of_property_set_flag(new, OF_DYNAMIC);

	return new;

 err_free:
	kfree(new->name);
	kfree(new->value);
	kfree(new);
	return NULL;
}
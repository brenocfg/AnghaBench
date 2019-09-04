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
struct property {struct property* next; int /*<<< orphan*/  name; } ;
struct device_node {struct property* deadprops; struct property* properties; } ;

/* Variables and functions */
 scalar_t__ of_prop_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __of_update_property(struct device_node *np, struct property *newprop,
		struct property **oldpropp)
{
	struct property **next, *oldprop;

	for (next = &np->properties; *next; next = &(*next)->next) {
		if (of_prop_cmp((*next)->name, newprop->name) == 0)
			break;
	}
	*oldpropp = oldprop = *next;

	if (oldprop) {
		/* replace the node */
		newprop->next = oldprop->next;
		*next = newprop;
		oldprop->next = np->deadprops;
		np->deadprops = oldprop;
	} else {
		/* new node */
		newprop->next = NULL;
		*next = newprop;
	}

	return 0;
}
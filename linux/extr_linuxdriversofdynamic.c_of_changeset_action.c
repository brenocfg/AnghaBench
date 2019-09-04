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
struct property {int /*<<< orphan*/  name; } ;
struct of_changeset_entry {unsigned long action; int /*<<< orphan*/  node; int /*<<< orphan*/  old_prop; struct property* prop; int /*<<< orphan*/  np; } ;
struct of_changeset {int /*<<< orphan*/  entries; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long OF_RECONFIG_UPDATE_PROPERTY ; 
 struct of_changeset_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 

int of_changeset_action(struct of_changeset *ocs, unsigned long action,
		struct device_node *np, struct property *prop)
{
	struct of_changeset_entry *ce;

	ce = kzalloc(sizeof(*ce), GFP_KERNEL);
	if (!ce)
		return -ENOMEM;

	/* get a reference to the node */
	ce->action = action;
	ce->np = of_node_get(np);
	ce->prop = prop;

	if (action == OF_RECONFIG_UPDATE_PROPERTY && prop)
		ce->old_prop = of_find_property(np, prop->name, NULL);

	/* add it to the list */
	list_add_tail(&ce->node, &ocs->entries);
	return 0;
}
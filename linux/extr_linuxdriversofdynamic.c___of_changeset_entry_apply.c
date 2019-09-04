#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct property {int /*<<< orphan*/  name; struct property* next; } ;
struct of_changeset_entry {int action; int /*<<< orphan*/  old_prop; struct property* prop; TYPE_1__* np; } ;
struct TYPE_12__ {struct property* deadprops; } ;

/* Variables and functions */
 int EINVAL ; 
#define  OF_RECONFIG_ADD_PROPERTY 132 
#define  OF_RECONFIG_ATTACH_NODE 131 
#define  OF_RECONFIG_DETACH_NODE 130 
#define  OF_RECONFIG_REMOVE_PROPERTY 129 
#define  OF_RECONFIG_UPDATE_PROPERTY 128 
 int __of_add_property (TYPE_1__*,struct property*) ; 
 int /*<<< orphan*/  __of_add_property_sysfs (TYPE_1__*,struct property*) ; 
 int /*<<< orphan*/  __of_attach_node (TYPE_1__*) ; 
 int /*<<< orphan*/  __of_attach_node_sysfs (TYPE_1__*) ; 
 int /*<<< orphan*/  __of_changeset_entry_dump (struct of_changeset_entry*) ; 
 int /*<<< orphan*/  __of_detach_node (TYPE_1__*) ; 
 int /*<<< orphan*/  __of_detach_node_sysfs (TYPE_1__*) ; 
 int __of_remove_property (TYPE_1__*,struct property*) ; 
 int /*<<< orphan*/  __of_remove_property_sysfs (TYPE_1__*,struct property*) ; 
 int __of_update_property (TYPE_1__*,struct property*,struct property**) ; 
 int /*<<< orphan*/  __of_update_property_sysfs (TYPE_1__*,struct property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  pr_err (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __of_changeset_entry_apply(struct of_changeset_entry *ce)
{
	struct property *old_prop, **propp;
	unsigned long flags;
	int ret = 0;

	__of_changeset_entry_dump(ce);

	raw_spin_lock_irqsave(&devtree_lock, flags);
	switch (ce->action) {
	case OF_RECONFIG_ATTACH_NODE:
		__of_attach_node(ce->np);
		break;
	case OF_RECONFIG_DETACH_NODE:
		__of_detach_node(ce->np);
		break;
	case OF_RECONFIG_ADD_PROPERTY:
		/* If the property is in deadprops then it must be removed */
		for (propp = &ce->np->deadprops; *propp; propp = &(*propp)->next) {
			if (*propp == ce->prop) {
				*propp = ce->prop->next;
				ce->prop->next = NULL;
				break;
			}
		}

		ret = __of_add_property(ce->np, ce->prop);
		if (ret) {
			pr_err("changeset: add_property failed @%pOF/%s\n",
				ce->np,
				ce->prop->name);
			break;
		}
		break;
	case OF_RECONFIG_REMOVE_PROPERTY:
		ret = __of_remove_property(ce->np, ce->prop);
		if (ret) {
			pr_err("changeset: remove_property failed @%pOF/%s\n",
				ce->np,
				ce->prop->name);
			break;
		}
		break;

	case OF_RECONFIG_UPDATE_PROPERTY:
		/* If the property is in deadprops then it must be removed */
		for (propp = &ce->np->deadprops; *propp; propp = &(*propp)->next) {
			if (*propp == ce->prop) {
				*propp = ce->prop->next;
				ce->prop->next = NULL;
				break;
			}
		}

		ret = __of_update_property(ce->np, ce->prop, &old_prop);
		if (ret) {
			pr_err("changeset: update_property failed @%pOF/%s\n",
				ce->np,
				ce->prop->name);
			break;
		}
		break;
	default:
		ret = -EINVAL;
	}
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	if (ret)
		return ret;

	switch (ce->action) {
	case OF_RECONFIG_ATTACH_NODE:
		__of_attach_node_sysfs(ce->np);
		break;
	case OF_RECONFIG_DETACH_NODE:
		__of_detach_node_sysfs(ce->np);
		break;
	case OF_RECONFIG_ADD_PROPERTY:
		/* ignore duplicate names */
		__of_add_property_sysfs(ce->np, ce->prop);
		break;
	case OF_RECONFIG_REMOVE_PROPERTY:
		__of_remove_property_sysfs(ce->np, ce->prop);
		break;
	case OF_RECONFIG_UPDATE_PROPERTY:
		__of_update_property_sysfs(ce->np, ce->prop, ce->old_prop);
		break;
	}

	return 0;
}
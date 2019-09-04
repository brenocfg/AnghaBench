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
struct of_changeset_entry {int action; int /*<<< orphan*/  prop; int /*<<< orphan*/  old_prop; } ;

/* Variables and functions */
#define  OF_RECONFIG_ADD_PROPERTY 132 
#define  OF_RECONFIG_ATTACH_NODE 131 
#define  OF_RECONFIG_DETACH_NODE 130 
#define  OF_RECONFIG_REMOVE_PROPERTY 129 
#define  OF_RECONFIG_UPDATE_PROPERTY 128 
 int /*<<< orphan*/  memcpy (struct of_changeset_entry*,struct of_changeset_entry*,int) ; 

__attribute__((used)) static void __of_changeset_entry_invert(struct of_changeset_entry *ce,
					  struct of_changeset_entry *rce)
{
	memcpy(rce, ce, sizeof(*rce));

	switch (ce->action) {
	case OF_RECONFIG_ATTACH_NODE:
		rce->action = OF_RECONFIG_DETACH_NODE;
		break;
	case OF_RECONFIG_DETACH_NODE:
		rce->action = OF_RECONFIG_ATTACH_NODE;
		break;
	case OF_RECONFIG_ADD_PROPERTY:
		rce->action = OF_RECONFIG_REMOVE_PROPERTY;
		break;
	case OF_RECONFIG_REMOVE_PROPERTY:
		rce->action = OF_RECONFIG_ADD_PROPERTY;
		break;
	case OF_RECONFIG_UPDATE_PROPERTY:
		rce->old_prop = ce->prop;
		rce->prop = ce->old_prop;
		/* update was used but original property did not exist */
		if (!rce->prop) {
			rce->action = OF_RECONFIG_REMOVE_PROPERTY;
			rce->prop = ce->prop;
		}
		break;
	}
}
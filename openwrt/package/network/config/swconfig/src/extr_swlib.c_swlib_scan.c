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
struct switch_dev {scalar_t__ vlan_ops; scalar_t__ port_ops; scalar_t__ ops; int /*<<< orphan*/  id; } ;
struct attrlist_arg {scalar_t__* head; int /*<<< orphan*/ * prev; int /*<<< orphan*/  atype; int /*<<< orphan*/  id; struct switch_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_CMD_LIST_GLOBAL ; 
 int /*<<< orphan*/  SWITCH_CMD_LIST_PORT ; 
 int /*<<< orphan*/  SWITCH_CMD_LIST_VLAN ; 
 int /*<<< orphan*/  SWLIB_ATTR_GROUP_GLOBAL ; 
 int /*<<< orphan*/  SWLIB_ATTR_GROUP_PORT ; 
 int /*<<< orphan*/  SWLIB_ATTR_GROUP_VLAN ; 
 int /*<<< orphan*/  add_attr ; 
 int /*<<< orphan*/  add_id ; 
 int /*<<< orphan*/  swlib_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct attrlist_arg*) ; 

int
swlib_scan(struct switch_dev *dev)
{
	struct attrlist_arg arg;

	if (dev->ops || dev->port_ops || dev->vlan_ops)
		return 0;

	arg.atype = SWLIB_ATTR_GROUP_GLOBAL;
	arg.dev = dev;
	arg.id = dev->id;
	arg.prev = NULL;
	arg.head = &dev->ops;
	swlib_call(SWITCH_CMD_LIST_GLOBAL, add_attr, add_id, &arg);

	arg.atype = SWLIB_ATTR_GROUP_PORT;
	arg.prev = NULL;
	arg.head = &dev->port_ops;
	swlib_call(SWITCH_CMD_LIST_PORT, add_attr, add_id, &arg);

	arg.atype = SWLIB_ATTR_GROUP_VLAN;
	arg.prev = NULL;
	arg.head = &dev->vlan_ops;
	swlib_call(SWITCH_CMD_LIST_VLAN, add_attr, add_id, &arg);

	return 0;
}
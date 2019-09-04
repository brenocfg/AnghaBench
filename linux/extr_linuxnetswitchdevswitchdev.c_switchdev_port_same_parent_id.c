#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ppid; } ;
struct switchdev_attr {TYPE_1__ u; int /*<<< orphan*/  id; struct net_device* orig_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_PORT_PARENT_ID ; 
 int netdev_phys_item_id_same (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ switchdev_port_attr_get (struct net_device*,struct switchdev_attr*) ; 

bool switchdev_port_same_parent_id(struct net_device *a,
				   struct net_device *b)
{
	struct switchdev_attr a_attr = {
		.orig_dev = a,
		.id = SWITCHDEV_ATTR_ID_PORT_PARENT_ID,
	};
	struct switchdev_attr b_attr = {
		.orig_dev = b,
		.id = SWITCHDEV_ATTR_ID_PORT_PARENT_ID,
	};

	if (switchdev_port_attr_get(a, &a_attr) ||
	    switchdev_port_attr_get(b, &b_attr))
		return false;

	return netdev_phys_item_id_same(&a_attr.u.ppid, &b_attr.u.ppid);
}
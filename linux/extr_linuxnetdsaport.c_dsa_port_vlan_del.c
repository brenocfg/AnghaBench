#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  orig_dev; } ;
struct switchdev_obj_port_vlan {TYPE_2__ obj; } ;
struct dsa_port {int /*<<< orphan*/  bridge_dev; int /*<<< orphan*/  index; TYPE_1__* ds; } ;
struct dsa_notifier_vlan_info {struct switchdev_obj_port_vlan const* vlan; int /*<<< orphan*/  port; int /*<<< orphan*/  sw_index; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_NOTIFIER_VLAN_DEL ; 
 int EOPNOTSUPP ; 
 scalar_t__ br_vlan_enabled (int /*<<< orphan*/ ) ; 
 int dsa_port_notify (struct dsa_port*,int /*<<< orphan*/ ,struct dsa_notifier_vlan_info*) ; 
 scalar_t__ netif_is_bridge_master (int /*<<< orphan*/ ) ; 

int dsa_port_vlan_del(struct dsa_port *dp,
		      const struct switchdev_obj_port_vlan *vlan)
{
	struct dsa_notifier_vlan_info info = {
		.sw_index = dp->ds->index,
		.port = dp->index,
		.vlan = vlan,
	};

	if (netif_is_bridge_master(vlan->obj.orig_dev))
		return -EOPNOTSUPP;

	if (br_vlan_enabled(dp->bridge_dev))
		return dsa_port_notify(dp, DSA_NOTIFIER_VLAN_DEL, &info);

	return 0;
}
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
struct switchdev_obj_port_vlan {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  index; TYPE_1__* ds; } ;
struct dsa_notifier_vlan_info {struct switchdev_obj_port_vlan const* vlan; int /*<<< orphan*/  port; int /*<<< orphan*/  sw_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_NOTIFIER_VLAN_DEL ; 
 int dsa_port_notify (struct dsa_port*,int /*<<< orphan*/ ,struct dsa_notifier_vlan_info*) ; 

int dsa_port_vlan_del(struct dsa_port *dp,
		      const struct switchdev_obj_port_vlan *vlan)
{
	struct dsa_notifier_vlan_info info = {
		.sw_index = dp->ds->index,
		.port = dp->index,
		.vlan = vlan,
	};

	return dsa_port_notify(dp, DSA_NOTIFIER_VLAN_DEL, &info);
}
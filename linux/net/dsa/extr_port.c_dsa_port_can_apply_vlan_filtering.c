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
struct net_device {int dummy; } ;
struct dsa_switch {int num_ports; int /*<<< orphan*/  dev; int /*<<< orphan*/  vlan_filtering_is_global; } ;
struct dsa_port {struct net_device* bridge_dev; struct dsa_switch* ds; } ;
struct TYPE_2__ {struct net_device* bridge_dev; } ;

/* Variables and functions */
 int br_vlan_enabled (struct net_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* dsa_to_port (struct dsa_switch*,int) ; 

__attribute__((used)) static bool dsa_port_can_apply_vlan_filtering(struct dsa_port *dp,
					      bool vlan_filtering)
{
	struct dsa_switch *ds = dp->ds;
	int i;

	if (!ds->vlan_filtering_is_global)
		return true;

	/* For cases where enabling/disabling VLAN awareness is global to the
	 * switch, we need to handle the case where multiple bridges span
	 * different ports of the same switch device and one of them has a
	 * different setting than what is being requested.
	 */
	for (i = 0; i < ds->num_ports; i++) {
		struct net_device *other_bridge;

		other_bridge = dsa_to_port(ds, i)->bridge_dev;
		if (!other_bridge)
			continue;
		/* If it's the same bridge, it also has same
		 * vlan_filtering setting => no need to check
		 */
		if (other_bridge == dp->bridge_dev)
			continue;
		if (br_vlan_enabled(other_bridge) != vlan_filtering) {
			dev_err(ds->dev, "VLAN filtering is a global setting\n");
			return false;
		}
	}
	return true;
}
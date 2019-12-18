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
struct switchdev_obj_port_vlan {int dummy; } ;
struct dsa_switch {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  slave; int /*<<< orphan*/  bridge_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_port_vlan_device_check ; 
 struct dsa_port* dsa_to_port (struct dsa_switch*,int) ; 
 int vlan_for_each (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int dsa_port_vlan_check(struct dsa_switch *ds, int port,
			       const struct switchdev_obj_port_vlan *vlan)
{
	const struct dsa_port *dp = dsa_to_port(ds, port);
	int err = 0;

	/* Device is not bridged, let it proceed with the VLAN device
	 * creation.
	 */
	if (!dp->bridge_dev)
		return err;

	/* dsa_slave_vlan_rx_{add,kill}_vid() cannot use the prepare phase and
	 * already checks whether there is an overlapping bridge VLAN entry
	 * with the same VID, so here we only need to check that if we are
	 * adding a bridge VLAN entry there is not an overlapping VLAN device
	 * claiming that VID.
	 */
	return vlan_for_each(dp->slave, dsa_port_vlan_device_check,
			     (void *)vlan);
}
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
struct ofdpa_port {struct net_device* bridge_dev; int /*<<< orphan*/  internal_vlan_id; TYPE_1__* dev; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFDPA_UNTAGGED_VID ; 
 int /*<<< orphan*/  ofdpa_port_internal_vlan_id_get (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_port_internal_vlan_id_put (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int ofdpa_port_vlan_add (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofdpa_port_vlan_del (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_bridge_join(struct ofdpa_port *ofdpa_port,
				  struct net_device *bridge)
{
	int err;

	/* Port is joining bridge, so the internal VLAN for the
	 * port is going to change to the bridge internal VLAN.
	 * Let's remove untagged VLAN (vid=0) from port and
	 * re-add once internal VLAN has changed.
	 */

	err = ofdpa_port_vlan_del(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
	if (err)
		return err;

	ofdpa_port_internal_vlan_id_put(ofdpa_port,
					ofdpa_port->dev->ifindex);
	ofdpa_port->internal_vlan_id =
		ofdpa_port_internal_vlan_id_get(ofdpa_port, bridge->ifindex);

	ofdpa_port->bridge_dev = bridge;

	return ofdpa_port_vlan_add(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
}
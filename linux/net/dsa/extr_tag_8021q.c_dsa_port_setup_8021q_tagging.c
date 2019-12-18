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
typedef  int u16 ;
struct dsa_switch {int num_ports; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int dsa_8021q_restore_pvid (struct dsa_switch*,int) ; 
 int dsa_8021q_rx_vid (struct dsa_switch*,int) ; 
 int dsa_8021q_tx_vid (struct dsa_switch*,int) ; 
 int dsa_8021q_vid_apply (struct dsa_switch*,int,int,int,int) ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int dsa_upstream_port (struct dsa_switch*,int) ; 

int dsa_port_setup_8021q_tagging(struct dsa_switch *ds, int port, bool enabled)
{
	int upstream = dsa_upstream_port(ds, port);
	u16 rx_vid = dsa_8021q_rx_vid(ds, port);
	u16 tx_vid = dsa_8021q_tx_vid(ds, port);
	int i, err;

	/* The CPU port is implicitly configured by
	 * configuring the front-panel ports
	 */
	if (!dsa_is_user_port(ds, port))
		return 0;

	/* Add this user port's RX VID to the membership list of all others
	 * (including itself). This is so that bridging will not be hindered.
	 * L2 forwarding rules still take precedence when there are no VLAN
	 * restrictions, so there are no concerns about leaking traffic.
	 */
	for (i = 0; i < ds->num_ports; i++) {
		u16 flags;

		if (i == upstream)
			continue;
		else if (i == port)
			/* The RX VID is pvid on this port */
			flags = BRIDGE_VLAN_INFO_UNTAGGED |
				BRIDGE_VLAN_INFO_PVID;
		else
			/* The RX VID is a regular VLAN on all others */
			flags = BRIDGE_VLAN_INFO_UNTAGGED;

		err = dsa_8021q_vid_apply(ds, i, rx_vid, flags, enabled);
		if (err) {
			dev_err(ds->dev, "Failed to apply RX VID %d to port %d: %d\n",
				rx_vid, port, err);
			return err;
		}
	}

	/* CPU port needs to see this port's RX VID
	 * as tagged egress.
	 */
	err = dsa_8021q_vid_apply(ds, upstream, rx_vid, 0, enabled);
	if (err) {
		dev_err(ds->dev, "Failed to apply RX VID %d to port %d: %d\n",
			rx_vid, port, err);
		return err;
	}

	/* Finally apply the TX VID on this port and on the CPU port */
	err = dsa_8021q_vid_apply(ds, port, tx_vid, BRIDGE_VLAN_INFO_UNTAGGED,
				  enabled);
	if (err) {
		dev_err(ds->dev, "Failed to apply TX VID %d on port %d: %d\n",
			tx_vid, port, err);
		return err;
	}
	err = dsa_8021q_vid_apply(ds, upstream, tx_vid, 0, enabled);
	if (err) {
		dev_err(ds->dev, "Failed to apply TX VID %d on port %d: %d\n",
			tx_vid, upstream, err);
		return err;
	}

	if (!enabled)
		err = dsa_8021q_restore_pvid(ds, port);

	return err;
}
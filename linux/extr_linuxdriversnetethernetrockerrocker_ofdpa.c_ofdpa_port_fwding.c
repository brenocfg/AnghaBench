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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ofdpa_port {scalar_t__ stp_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  vlan_bitmap; int /*<<< orphan*/  pport; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 int OFDPA_OP_FLAG_REMOVE ; 
 int VLAN_N_VID ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int ofdpa_group_l2_interface (struct ofdpa_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ofdpa_vlan_id_is_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_fwding(struct ofdpa_port *ofdpa_port, int flags)
{
	bool pop_vlan;
	u32 out_pport;
	__be16 vlan_id;
	u16 vid;
	int err;

	/* Port will be forwarding-enabled if its STP state is LEARNING
	 * or FORWARDING.  Traffic from CPU can still egress, regardless of
	 * port STP state.  Use L2 interface group on port VLANs as a way
	 * to toggle port forwarding: if forwarding is disabled, L2
	 * interface group will not exist.
	 */

	if (ofdpa_port->stp_state != BR_STATE_LEARNING &&
	    ofdpa_port->stp_state != BR_STATE_FORWARDING)
		flags |= OFDPA_OP_FLAG_REMOVE;

	out_pport = ofdpa_port->pport;
	for (vid = 1; vid < VLAN_N_VID; vid++) {
		if (!test_bit(vid, ofdpa_port->vlan_bitmap))
			continue;
		vlan_id = htons(vid);
		pop_vlan = ofdpa_vlan_id_is_internal(vlan_id);
		err = ofdpa_group_l2_interface(ofdpa_port, flags,
					       vlan_id, out_pport, pop_vlan);
		if (err) {
			netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 group for pport %d\n",
				   err, out_pport);
			return err;
		}
	}

	return 0;
}
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
typedef  scalar_t__ u32 ;
struct ofdpa_port {scalar_t__ stp_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  vlan_bitmap; scalar_t__ pport; struct ofdpa* ofdpa; } ;
struct ofdpa {TYPE_1__* rocker; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {unsigned int port_count; } ;

/* Variables and functions */
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 int OFDPA_OP_FLAG_REMOVE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int ofdpa_group_l2_interface (struct ofdpa_port*,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct ofdpa_port* ofdpa_port_get (struct ofdpa const*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_vlan_l2_groups(struct ofdpa_port *ofdpa_port, int flags,
				     __be16 vlan_id, bool pop_vlan)
{
	const struct ofdpa *ofdpa = ofdpa_port->ofdpa;
	unsigned int port_count = ofdpa->rocker->port_count;
	struct ofdpa_port *p;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	u32 out_pport;
	int ref = 0;
	int err;
	int i;

	/* An L2 interface group for this port in this VLAN, but
	 * only when port STP state is LEARNING|FORWARDING.
	 */

	if (ofdpa_port->stp_state == BR_STATE_LEARNING ||
	    ofdpa_port->stp_state == BR_STATE_FORWARDING) {
		out_pport = ofdpa_port->pport;
		err = ofdpa_group_l2_interface(ofdpa_port, flags,
					       vlan_id, out_pport, pop_vlan);
		if (err) {
			netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 group for pport %d\n",
				   err, out_pport);
			return err;
		}
	}

	/* An L2 interface group for this VLAN to CPU port.
	 * Add when first port joins this VLAN and destroy when
	 * last port leaves this VLAN.
	 */

	for (i = 0; i < port_count; i++) {
		p = ofdpa_port_get(ofdpa, i);
		if (p && test_bit(ntohs(vlan_id), p->vlan_bitmap))
			ref++;
	}

	if ((!adding || ref != 1) && (adding || ref != 0))
		return 0;

	out_pport = 0;
	err = ofdpa_group_l2_interface(ofdpa_port, flags,
				       vlan_id, out_pport, pop_vlan);
	if (err) {
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 group for CPU port\n", err);
		return err;
	}

	return 0;
}
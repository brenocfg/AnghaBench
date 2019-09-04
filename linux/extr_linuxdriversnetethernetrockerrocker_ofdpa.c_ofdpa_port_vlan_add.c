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
typedef  int /*<<< orphan*/  u16 ;
struct ofdpa_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFDPA_OP_FLAG_REMOVE ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int ofdpa_port_router_mac (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ofdpa_port_vlan (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_vlan_add(struct ofdpa_port *ofdpa_port,
			       u16 vid, u16 flags)
{
	int err;

	/* XXX deal with flags for PVID and untagged */

	err = ofdpa_port_vlan(ofdpa_port, 0, vid);
	if (err)
		return err;

	err = ofdpa_port_router_mac(ofdpa_port, 0, htons(vid));
	if (err)
		ofdpa_port_vlan(ofdpa_port,
				OFDPA_OP_FLAG_REMOVE, vid);

	return err;
}
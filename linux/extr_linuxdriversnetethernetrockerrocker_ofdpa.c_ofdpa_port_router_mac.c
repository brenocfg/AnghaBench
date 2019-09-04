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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ofdpa_port {TYPE_1__* dev; int /*<<< orphan*/  pport; int /*<<< orphan*/  internal_vlan_id; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int /*<<< orphan*/ * ff_mac ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int ofdpa_flow_tbl_term_mac (struct ofdpa_port*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ofdpa_port_router_mac(struct ofdpa_port *ofdpa_port,
				 int flags, __be16 vlan_id)
{
	u32 in_pport_mask = 0xffffffff;
	__be16 eth_type;
	const u8 *dst_mac_mask = ff_mac;
	__be16 vlan_id_mask = htons(0xffff);
	bool copy_to_cpu = false;
	int err;

	if (ntohs(vlan_id) == 0)
		vlan_id = ofdpa_port->internal_vlan_id;

	eth_type = htons(ETH_P_IP);
	err = ofdpa_flow_tbl_term_mac(ofdpa_port, ofdpa_port->pport,
				      in_pport_mask, eth_type,
				      ofdpa_port->dev->dev_addr,
				      dst_mac_mask, vlan_id, vlan_id_mask,
				      copy_to_cpu, flags);
	if (err)
		return err;

	eth_type = htons(ETH_P_IPV6);
	err = ofdpa_flow_tbl_term_mac(ofdpa_port, ofdpa_port->pport,
				      in_pport_mask, eth_type,
				      ofdpa_port->dev->dev_addr,
				      dst_mac_mask, vlan_id, vlan_id_mask,
				      copy_to_cpu, flags);

	return err;
}
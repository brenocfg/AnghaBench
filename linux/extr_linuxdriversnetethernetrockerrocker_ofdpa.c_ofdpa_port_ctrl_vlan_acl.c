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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ofdpa_port {int pport; int /*<<< orphan*/  dev; } ;
struct ofdpa_ctrl {int /*<<< orphan*/  eth_type; int /*<<< orphan*/  eth_dst_mask; int /*<<< orphan*/  eth_dst; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ROCKER_GROUP_L2_INTERFACE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ofdpa_flow_tbl_acl (struct ofdpa_port*,int,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ofdpa_port_ctrl_vlan_acl(struct ofdpa_port *ofdpa_port, int flags,
				    const struct ofdpa_ctrl *ctrl, __be16 vlan_id)
{
	u32 in_pport = ofdpa_port->pport;
	u32 in_pport_mask = 0xffffffff;
	u32 out_pport = 0;
	const u8 *eth_src = NULL;
	const u8 *eth_src_mask = NULL;
	__be16 vlan_id_mask = htons(0xffff);
	u8 ip_proto = 0;
	u8 ip_proto_mask = 0;
	u8 ip_tos = 0;
	u8 ip_tos_mask = 0;
	u32 group_id = ROCKER_GROUP_L2_INTERFACE(vlan_id, out_pport);
	int err;

	err = ofdpa_flow_tbl_acl(ofdpa_port, flags,
				 in_pport, in_pport_mask,
				 eth_src, eth_src_mask,
				 ctrl->eth_dst, ctrl->eth_dst_mask,
				 ctrl->eth_type,
				 vlan_id, vlan_id_mask,
				 ip_proto, ip_proto_mask,
				 ip_tos, ip_tos_mask,
				 group_id);

	if (err)
		netdev_err(ofdpa_port->dev, "Error (%d) ctrl ACL\n", err);

	return err;
}
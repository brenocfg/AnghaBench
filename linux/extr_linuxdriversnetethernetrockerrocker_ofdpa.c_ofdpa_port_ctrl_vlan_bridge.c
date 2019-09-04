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
struct ofdpa_port {int /*<<< orphan*/  dev; } ;
struct ofdpa_ctrl {int /*<<< orphan*/  copy_to_cpu; int /*<<< orphan*/  eth_dst_mask; int /*<<< orphan*/  eth_dst; } ;
typedef  enum rocker_of_dpa_table_id { ____Placeholder_rocker_of_dpa_table_id } rocker_of_dpa_table_id ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_GROUP_L2_FLOOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ROCKER_OF_DPA_TABLE_ID_ACL_POLICY ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ofdpa_flow_tbl_bridge (struct ofdpa_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofdpa_port_is_bridged (struct ofdpa_port*) ; 

__attribute__((used)) static int ofdpa_port_ctrl_vlan_bridge(struct ofdpa_port *ofdpa_port,
				       int flags, const struct ofdpa_ctrl *ctrl,
				       __be16 vlan_id)
{
	enum rocker_of_dpa_table_id goto_tbl =
			ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id = ROCKER_GROUP_L2_FLOOD(vlan_id, 0);
	u32 tunnel_id = 0;
	int err;

	if (!ofdpa_port_is_bridged(ofdpa_port))
		return 0;

	err = ofdpa_flow_tbl_bridge(ofdpa_port, flags,
				    ctrl->eth_dst, ctrl->eth_dst_mask,
				    vlan_id, tunnel_id,
				    goto_tbl, group_id, ctrl->copy_to_cpu);

	if (err)
		netdev_err(ofdpa_port->dev, "Error (%d) ctrl FLOOD\n", err);

	return err;
}
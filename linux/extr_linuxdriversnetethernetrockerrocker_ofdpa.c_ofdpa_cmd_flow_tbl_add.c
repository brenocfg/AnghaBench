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
struct rocker_tlv {int dummy; } ;
struct rocker_port {int dummy; } ;
struct rocker_desc_info {int dummy; } ;
struct TYPE_2__ {int tbl_id; int /*<<< orphan*/  priority; } ;
struct ofdpa_flow_tbl_entry {int cmd; TYPE_1__ key; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOTSUPP ; 
#define  ROCKER_OF_DPA_TABLE_ID_ACL_POLICY 133 
#define  ROCKER_OF_DPA_TABLE_ID_BRIDGING 132 
#define  ROCKER_OF_DPA_TABLE_ID_INGRESS_PORT 131 
#define  ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC 130 
#define  ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING 129 
#define  ROCKER_OF_DPA_TABLE_ID_VLAN 128 
 int /*<<< orphan*/  ROCKER_TLV_CMD_INFO ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_COOKIE ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_HARDTIME ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_PRIORITY ; 
 int /*<<< orphan*/  ROCKER_TLV_OF_DPA_TABLE_ID ; 
 int ofdpa_cmd_flow_tbl_add_acl (struct rocker_desc_info*,struct ofdpa_flow_tbl_entry const*) ; 
 int ofdpa_cmd_flow_tbl_add_bridge (struct rocker_desc_info*,struct ofdpa_flow_tbl_entry const*) ; 
 int ofdpa_cmd_flow_tbl_add_ig_port (struct rocker_desc_info*,struct ofdpa_flow_tbl_entry const*) ; 
 int ofdpa_cmd_flow_tbl_add_term_mac (struct rocker_desc_info*,struct ofdpa_flow_tbl_entry const*) ; 
 int ofdpa_cmd_flow_tbl_add_ucast_routing (struct rocker_desc_info*,struct ofdpa_flow_tbl_entry const*) ; 
 int ofdpa_cmd_flow_tbl_add_vlan (struct rocker_desc_info*,struct ofdpa_flow_tbl_entry const*) ; 
 int /*<<< orphan*/  rocker_tlv_nest_end (struct rocker_desc_info*,struct rocker_tlv*) ; 
 struct rocker_tlv* rocker_tlv_nest_start (struct rocker_desc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rocker_tlv_put_u32 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u64 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_cmd_flow_tbl_add(const struct rocker_port *rocker_port,
				  struct rocker_desc_info *desc_info,
				  void *priv)
{
	const struct ofdpa_flow_tbl_entry *entry = priv;
	struct rocker_tlv *cmd_info;
	int err = 0;

	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE, entry->cmd))
		return -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	if (!cmd_info)
		return -EMSGSIZE;
	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_TABLE_ID,
			       entry->key.tbl_id))
		return -EMSGSIZE;
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_PRIORITY,
			       entry->key.priority))
		return -EMSGSIZE;
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_HARDTIME, 0))
		return -EMSGSIZE;
	if (rocker_tlv_put_u64(desc_info, ROCKER_TLV_OF_DPA_COOKIE,
			       entry->cookie))
		return -EMSGSIZE;

	switch (entry->key.tbl_id) {
	case ROCKER_OF_DPA_TABLE_ID_INGRESS_PORT:
		err = ofdpa_cmd_flow_tbl_add_ig_port(desc_info, entry);
		break;
	case ROCKER_OF_DPA_TABLE_ID_VLAN:
		err = ofdpa_cmd_flow_tbl_add_vlan(desc_info, entry);
		break;
	case ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC:
		err = ofdpa_cmd_flow_tbl_add_term_mac(desc_info, entry);
		break;
	case ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING:
		err = ofdpa_cmd_flow_tbl_add_ucast_routing(desc_info, entry);
		break;
	case ROCKER_OF_DPA_TABLE_ID_BRIDGING:
		err = ofdpa_cmd_flow_tbl_add_bridge(desc_info, entry);
		break;
	case ROCKER_OF_DPA_TABLE_ID_ACL_POLICY:
		err = ofdpa_cmd_flow_tbl_add_acl(desc_info, entry);
		break;
	default:
		err = -ENOTSUPP;
		break;
	}

	if (err)
		return err;

	rocker_tlv_nest_end(desc_info, cmd_info);

	return 0;
}
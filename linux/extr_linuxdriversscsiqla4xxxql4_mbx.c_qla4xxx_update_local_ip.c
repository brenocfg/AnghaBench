#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* u6_addr8; } ;
struct TYPE_5__ {TYPE_1__ in6_u; } ;
struct TYPE_6__ {int tcp_options; int ipv4_options; int eth_mtu_size; int ipv4_port; int ipv6_options; int ipv6_addl_options; int ipv6_tcp_options; int* ip_address; int* subnet_mask; int* gateway; int* ipv4_alt_cid; int* ipv4_vid; int def_timeout; int iscsi_options; int iscsi_max_pdu_size; int iscsi_first_burst_len; int iscsi_max_outstnd_r2t; int iscsi_max_burst_len; int* iscsi_name; int ipv6_addr0; int ipv6_addr1; int ipv6_default_router_addr; int ipv6_port; int ipv6_flow_lbl; int /*<<< orphan*/  ipv6_tcp_wsf; void* ipv6_gw_advrt_mtu; int /*<<< orphan*/  ipv6_dup_addr_detect_count; void* ipv6_nd_stale_timeout; void* ipv6_nd_rexmit_timer; void* ipv6_nd_reach_time; int /*<<< orphan*/  ipv6_hop_limit; int /*<<< orphan*/  ipv6_traffic_class; int /*<<< orphan*/  ipv6_cache_id; void* ipv6_vlan_tag; TYPE_2__ ipv6_link_local_addr; void* ipv6_default_router_state; void* ipv6_addr1_state; void* ipv6_addr0_state; void* ipv6_link_local_state; int /*<<< orphan*/  abort_timer; int /*<<< orphan*/  ipv4_ttl; int /*<<< orphan*/  ipv4_vid_len; int /*<<< orphan*/  ipv4_alt_cid_len; int /*<<< orphan*/  ipv4_cache_id; int /*<<< orphan*/  ipv4_tos; int /*<<< orphan*/  tcp_wsf; int /*<<< orphan*/  control; void* ipv4_vlan_tag; void* ipv4_addr_state; } ;
struct scsi_qla_host {scalar_t__ acb_version; TYPE_3__ ip_config; } ;
struct addr_ctrl_blk {int /*<<< orphan*/  ipv6_tcp_wsf; int /*<<< orphan*/  ipv6_gw_advrt_mtu; int /*<<< orphan*/  ipv6_dup_addr_detect_count; int /*<<< orphan*/  ipv6_nd_stale_timeout; int /*<<< orphan*/  ipv6_nd_rexmit_timer; int /*<<< orphan*/  ipv6_nd_reach_time; int /*<<< orphan*/  ipv6_hop_limit; int /*<<< orphan*/  ipv6_traffic_class; int /*<<< orphan*/  ipv6_flow_lbl; int /*<<< orphan*/  ipv6_cache_id; int /*<<< orphan*/  ipv6_port; int /*<<< orphan*/  ipv6_vlan_tag; int /*<<< orphan*/  ipv6_dflt_rtr_addr; int /*<<< orphan*/  ipv6_addr1; int /*<<< orphan*/  ipv6_addr0; int /*<<< orphan*/  ipv6_if_id; int /*<<< orphan*/  ipv6_dflt_rtr_state; int /*<<< orphan*/  ipv6_addr1_state; int /*<<< orphan*/  ipv6_addr0_state; int /*<<< orphan*/  ipv6_lnk_lcl_addr_state; int /*<<< orphan*/  iscsi_name; int /*<<< orphan*/  iscsi_max_burst_len; int /*<<< orphan*/  iscsi_max_outstnd_r2t; int /*<<< orphan*/  iscsi_fburst_len; int /*<<< orphan*/  iscsi_max_pdu_size; int /*<<< orphan*/  iscsi_opts; int /*<<< orphan*/  abort_timer; int /*<<< orphan*/  def_timeout; int /*<<< orphan*/  ipv4_ttl; int /*<<< orphan*/  ipv4_dhcp_vid; int /*<<< orphan*/  ipv4_dhcp_vid_len; int /*<<< orphan*/  ipv4_dhcp_alt_cid; int /*<<< orphan*/  ipv4_dhcp_alt_cid_len; int /*<<< orphan*/  ipv4_cacheid; int /*<<< orphan*/  ipv4_tos; int /*<<< orphan*/  ipv4_tcp_wsf; int /*<<< orphan*/  control; int /*<<< orphan*/  ipv4_vlan_tag; int /*<<< orphan*/  ipv4_gw_addr; int /*<<< orphan*/  ipv4_subnet; int /*<<< orphan*/  ipv4_addr; int /*<<< orphan*/  ipv6_tcp_opts; int /*<<< orphan*/  ipv6_addtl_opts; int /*<<< orphan*/  ipv6_opts; int /*<<< orphan*/  ipv4_port; int /*<<< orphan*/  eth_mtu_size; int /*<<< orphan*/  ipv4_addr_state; int /*<<< orphan*/  ipv4_ip_opts; int /*<<< orphan*/  ipv4_tcp_opts; } ;

/* Variables and functions */
 scalar_t__ ACB_SUPPORTED ; 
#define  IPV6_RTRSTATE_ADVERTISED 131 
#define  IPV6_RTRSTATE_MANUAL 130 
#define  IPV6_RTRSTATE_STALE 129 
#define  IPV6_RTRSTATE_UNKNOWN 128 
 void* ISCSI_ROUTER_STATE_ADVERTISED ; 
 void* ISCSI_ROUTER_STATE_MANUAL ; 
 void* ISCSI_ROUTER_STATE_STALE ; 
 void* ISCSI_ROUTER_STATE_UNKNOWN ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ipv6_enabled (struct scsi_qla_host*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 void* qla4xxx_set_ipaddr_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla4xxx_update_local_ip(struct scsi_qla_host *ha,
			struct addr_ctrl_blk *init_fw_cb)
{
	ha->ip_config.tcp_options = le16_to_cpu(init_fw_cb->ipv4_tcp_opts);
	ha->ip_config.ipv4_options = le16_to_cpu(init_fw_cb->ipv4_ip_opts);
	ha->ip_config.ipv4_addr_state =
			qla4xxx_set_ipaddr_state(init_fw_cb->ipv4_addr_state);
	ha->ip_config.eth_mtu_size =
				le16_to_cpu(init_fw_cb->eth_mtu_size);
	ha->ip_config.ipv4_port = le16_to_cpu(init_fw_cb->ipv4_port);

	if (ha->acb_version == ACB_SUPPORTED) {
		ha->ip_config.ipv6_options = le16_to_cpu(init_fw_cb->ipv6_opts);
		ha->ip_config.ipv6_addl_options =
				le16_to_cpu(init_fw_cb->ipv6_addtl_opts);
		ha->ip_config.ipv6_tcp_options =
				le16_to_cpu(init_fw_cb->ipv6_tcp_opts);
	}

	/* Save IPv4 Address Info */
	memcpy(ha->ip_config.ip_address, init_fw_cb->ipv4_addr,
	       min(sizeof(ha->ip_config.ip_address),
		   sizeof(init_fw_cb->ipv4_addr)));
	memcpy(ha->ip_config.subnet_mask, init_fw_cb->ipv4_subnet,
	       min(sizeof(ha->ip_config.subnet_mask),
		   sizeof(init_fw_cb->ipv4_subnet)));
	memcpy(ha->ip_config.gateway, init_fw_cb->ipv4_gw_addr,
	       min(sizeof(ha->ip_config.gateway),
		   sizeof(init_fw_cb->ipv4_gw_addr)));

	ha->ip_config.ipv4_vlan_tag = be16_to_cpu(init_fw_cb->ipv4_vlan_tag);
	ha->ip_config.control = init_fw_cb->control;
	ha->ip_config.tcp_wsf = init_fw_cb->ipv4_tcp_wsf;
	ha->ip_config.ipv4_tos = init_fw_cb->ipv4_tos;
	ha->ip_config.ipv4_cache_id = init_fw_cb->ipv4_cacheid;
	ha->ip_config.ipv4_alt_cid_len = init_fw_cb->ipv4_dhcp_alt_cid_len;
	memcpy(ha->ip_config.ipv4_alt_cid, init_fw_cb->ipv4_dhcp_alt_cid,
	       min(sizeof(ha->ip_config.ipv4_alt_cid),
		   sizeof(init_fw_cb->ipv4_dhcp_alt_cid)));
	ha->ip_config.ipv4_vid_len = init_fw_cb->ipv4_dhcp_vid_len;
	memcpy(ha->ip_config.ipv4_vid, init_fw_cb->ipv4_dhcp_vid,
	       min(sizeof(ha->ip_config.ipv4_vid),
		   sizeof(init_fw_cb->ipv4_dhcp_vid)));
	ha->ip_config.ipv4_ttl = init_fw_cb->ipv4_ttl;
	ha->ip_config.def_timeout = le16_to_cpu(init_fw_cb->def_timeout);
	ha->ip_config.abort_timer = init_fw_cb->abort_timer;
	ha->ip_config.iscsi_options = le16_to_cpu(init_fw_cb->iscsi_opts);
	ha->ip_config.iscsi_max_pdu_size =
				le16_to_cpu(init_fw_cb->iscsi_max_pdu_size);
	ha->ip_config.iscsi_first_burst_len =
				le16_to_cpu(init_fw_cb->iscsi_fburst_len);
	ha->ip_config.iscsi_max_outstnd_r2t =
				le16_to_cpu(init_fw_cb->iscsi_max_outstnd_r2t);
	ha->ip_config.iscsi_max_burst_len =
				le16_to_cpu(init_fw_cb->iscsi_max_burst_len);
	memcpy(ha->ip_config.iscsi_name, init_fw_cb->iscsi_name,
	       min(sizeof(ha->ip_config.iscsi_name),
		   sizeof(init_fw_cb->iscsi_name)));

	if (is_ipv6_enabled(ha)) {
		/* Save IPv6 Address */
		ha->ip_config.ipv6_link_local_state =
		  qla4xxx_set_ipaddr_state(init_fw_cb->ipv6_lnk_lcl_addr_state);
		ha->ip_config.ipv6_addr0_state =
			qla4xxx_set_ipaddr_state(init_fw_cb->ipv6_addr0_state);
		ha->ip_config.ipv6_addr1_state =
			qla4xxx_set_ipaddr_state(init_fw_cb->ipv6_addr1_state);

		switch (le16_to_cpu(init_fw_cb->ipv6_dflt_rtr_state)) {
		case IPV6_RTRSTATE_UNKNOWN:
			ha->ip_config.ipv6_default_router_state =
						ISCSI_ROUTER_STATE_UNKNOWN;
			break;
		case IPV6_RTRSTATE_MANUAL:
			ha->ip_config.ipv6_default_router_state =
						ISCSI_ROUTER_STATE_MANUAL;
			break;
		case IPV6_RTRSTATE_ADVERTISED:
			ha->ip_config.ipv6_default_router_state =
						ISCSI_ROUTER_STATE_ADVERTISED;
			break;
		case IPV6_RTRSTATE_STALE:
			ha->ip_config.ipv6_default_router_state =
						ISCSI_ROUTER_STATE_STALE;
			break;
		default:
			ha->ip_config.ipv6_default_router_state =
						ISCSI_ROUTER_STATE_UNKNOWN;
		}

		ha->ip_config.ipv6_link_local_addr.in6_u.u6_addr8[0] = 0xFE;
		ha->ip_config.ipv6_link_local_addr.in6_u.u6_addr8[1] = 0x80;

		memcpy(&ha->ip_config.ipv6_link_local_addr.in6_u.u6_addr8[8],
		       init_fw_cb->ipv6_if_id,
		       min(sizeof(ha->ip_config.ipv6_link_local_addr)/2,
			   sizeof(init_fw_cb->ipv6_if_id)));
		memcpy(&ha->ip_config.ipv6_addr0, init_fw_cb->ipv6_addr0,
		       min(sizeof(ha->ip_config.ipv6_addr0),
			   sizeof(init_fw_cb->ipv6_addr0)));
		memcpy(&ha->ip_config.ipv6_addr1, init_fw_cb->ipv6_addr1,
		       min(sizeof(ha->ip_config.ipv6_addr1),
			   sizeof(init_fw_cb->ipv6_addr1)));
		memcpy(&ha->ip_config.ipv6_default_router_addr,
		       init_fw_cb->ipv6_dflt_rtr_addr,
		       min(sizeof(ha->ip_config.ipv6_default_router_addr),
			   sizeof(init_fw_cb->ipv6_dflt_rtr_addr)));
		ha->ip_config.ipv6_vlan_tag =
				be16_to_cpu(init_fw_cb->ipv6_vlan_tag);
		ha->ip_config.ipv6_port = le16_to_cpu(init_fw_cb->ipv6_port);
		ha->ip_config.ipv6_cache_id = init_fw_cb->ipv6_cache_id;
		ha->ip_config.ipv6_flow_lbl =
				le16_to_cpu(init_fw_cb->ipv6_flow_lbl);
		ha->ip_config.ipv6_traffic_class =
				init_fw_cb->ipv6_traffic_class;
		ha->ip_config.ipv6_hop_limit = init_fw_cb->ipv6_hop_limit;
		ha->ip_config.ipv6_nd_reach_time =
				le32_to_cpu(init_fw_cb->ipv6_nd_reach_time);
		ha->ip_config.ipv6_nd_rexmit_timer =
				le32_to_cpu(init_fw_cb->ipv6_nd_rexmit_timer);
		ha->ip_config.ipv6_nd_stale_timeout =
				le32_to_cpu(init_fw_cb->ipv6_nd_stale_timeout);
		ha->ip_config.ipv6_dup_addr_detect_count =
					init_fw_cb->ipv6_dup_addr_detect_count;
		ha->ip_config.ipv6_gw_advrt_mtu =
				le32_to_cpu(init_fw_cb->ipv6_gw_advrt_mtu);
		ha->ip_config.ipv6_tcp_wsf = init_fw_cb->ipv6_tcp_wsf;
	}
}
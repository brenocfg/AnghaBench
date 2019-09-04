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
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct iscsi_bus_flash_session {int auto_snd_tgt_disable; int discovery_sess; int entry_state; int imm_data_en; int initial_r2t_en; int dataseq_inorder_en; int pdu_inorder_en; int chap_auth_en; int discovery_logout_en; int bidi_chap_en; int discovery_auth_optional; int erl; int max_r2t; int first_burst; int max_burst; int time2wait; int time2retain; int tpgt; int discovery_parent_idx; int chap_out_idx; int tsid; int default_taskmgmt_timeout; int /*<<< orphan*/  isid; scalar_t__ targetalias; scalar_t__ targetname; int /*<<< orphan*/  portal_type; } ;
struct iscsi_bus_flash_conn {int is_fw_assigned_ipv6; int hdrdgst_en; int datadgst_en; int snack_req_en; int tcp_timestamp_stat; int tcp_nagle_disable; int tcp_wsf_disable; int tcp_timer_scale; int tcp_timestamp_en; int fragment_disable; int max_recv_dlength; int max_xmit_dlength; int max_segment_size; int ipv6_flow_label; int keepalive_timeout; int local_port; int port; scalar_t__ link_local_ipv6_addr; scalar_t__ redirect_ipaddr; scalar_t__ ipaddress; int /*<<< orphan*/  ipv4_tos; int /*<<< orphan*/  ipv6_traffic_class; int /*<<< orphan*/  exp_statsn; int /*<<< orphan*/  statsn; int /*<<< orphan*/  tcp_recv_wsf; int /*<<< orphan*/  tcp_xmit_wsf; } ;
struct dev_db_entry {int /*<<< orphan*/  isid; int /*<<< orphan*/  iscsi_alias; int /*<<< orphan*/  iscsi_name; int /*<<< orphan*/  link_local_ipv6_addr; int /*<<< orphan*/  tgt_addr; int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  ipv4_tos; void* def_timeout; void* port; void* tsid; void* chap_tbl_idx; void* ddb_link; void* exp_stat_sn; void* stat_sn; void* lcl_port; void* ka_timeout; void* ipv6_flow_lbl; void* tcp_rcv_wsf; void* tcp_xmt_wsf; void* mss; void* tgt_portal_grp; void* iscsi_def_time2retain; void* iscsi_def_time2wait; void* iscsi_max_burst_len; void* iscsi_first_burst_len; void* iscsi_max_snd_data_seg_len; void* iscsi_max_rcv_data_seg_len; void* iscsi_max_outsnd_r2t; void* ip_options; void* tcp_options; void* iscsi_options; void* options; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_10 ; 
 int BIT_11 ; 
 int BIT_12 ; 
 int BIT_13 ; 
 int BIT_2 ; 
 int BIT_3 ; 
 int BIT_4 ; 
 int BIT_5 ; 
 int BIT_6 ; 
 int BIT_7 ; 
 int BIT_8 ; 
 int BIT_9 ; 
 int BYTE_UNITS ; 
 int /*<<< orphan*/  COPY_ISID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTAL_TYPE_IPV6 ; 
 int /*<<< orphan*/  SET_BITVAL (int,int,int) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qla4xxx_copy_to_fwddb_param(struct iscsi_bus_flash_session *sess,
				       struct iscsi_bus_flash_conn *conn,
				       struct dev_db_entry *fw_ddb_entry)
{
	uint16_t options;
	int rc = 0;

	options = le16_to_cpu(fw_ddb_entry->options);
	SET_BITVAL(conn->is_fw_assigned_ipv6,  options, BIT_11);
	if (!strncmp(sess->portal_type, PORTAL_TYPE_IPV6, 4))
		options |= BIT_8;
	else
		options &= ~BIT_8;

	SET_BITVAL(sess->auto_snd_tgt_disable, options, BIT_6);
	SET_BITVAL(sess->discovery_sess, options, BIT_4);
	SET_BITVAL(sess->entry_state, options, BIT_3);
	fw_ddb_entry->options = cpu_to_le16(options);

	options = le16_to_cpu(fw_ddb_entry->iscsi_options);
	SET_BITVAL(conn->hdrdgst_en, options, BIT_13);
	SET_BITVAL(conn->datadgst_en, options, BIT_12);
	SET_BITVAL(sess->imm_data_en, options, BIT_11);
	SET_BITVAL(sess->initial_r2t_en, options, BIT_10);
	SET_BITVAL(sess->dataseq_inorder_en, options, BIT_9);
	SET_BITVAL(sess->pdu_inorder_en, options, BIT_8);
	SET_BITVAL(sess->chap_auth_en, options, BIT_7);
	SET_BITVAL(conn->snack_req_en, options, BIT_6);
	SET_BITVAL(sess->discovery_logout_en, options, BIT_5);
	SET_BITVAL(sess->bidi_chap_en, options, BIT_4);
	SET_BITVAL(sess->discovery_auth_optional, options, BIT_3);
	SET_BITVAL(sess->erl & BIT_1, options, BIT_1);
	SET_BITVAL(sess->erl & BIT_0, options, BIT_0);
	fw_ddb_entry->iscsi_options = cpu_to_le16(options);

	options = le16_to_cpu(fw_ddb_entry->tcp_options);
	SET_BITVAL(conn->tcp_timestamp_stat, options, BIT_6);
	SET_BITVAL(conn->tcp_nagle_disable, options, BIT_5);
	SET_BITVAL(conn->tcp_wsf_disable, options, BIT_4);
	SET_BITVAL(conn->tcp_timer_scale & BIT_2, options, BIT_3);
	SET_BITVAL(conn->tcp_timer_scale & BIT_1, options, BIT_2);
	SET_BITVAL(conn->tcp_timer_scale & BIT_0, options, BIT_1);
	SET_BITVAL(conn->tcp_timestamp_en, options, BIT_0);
	fw_ddb_entry->tcp_options = cpu_to_le16(options);

	options = le16_to_cpu(fw_ddb_entry->ip_options);
	SET_BITVAL(conn->fragment_disable, options, BIT_4);
	fw_ddb_entry->ip_options = cpu_to_le16(options);

	fw_ddb_entry->iscsi_max_outsnd_r2t = cpu_to_le16(sess->max_r2t);
	fw_ddb_entry->iscsi_max_rcv_data_seg_len =
			       cpu_to_le16(conn->max_recv_dlength / BYTE_UNITS);
	fw_ddb_entry->iscsi_max_snd_data_seg_len =
			       cpu_to_le16(conn->max_xmit_dlength / BYTE_UNITS);
	fw_ddb_entry->iscsi_first_burst_len =
				cpu_to_le16(sess->first_burst / BYTE_UNITS);
	fw_ddb_entry->iscsi_max_burst_len = cpu_to_le16(sess->max_burst /
					    BYTE_UNITS);
	fw_ddb_entry->iscsi_def_time2wait = cpu_to_le16(sess->time2wait);
	fw_ddb_entry->iscsi_def_time2retain = cpu_to_le16(sess->time2retain);
	fw_ddb_entry->tgt_portal_grp = cpu_to_le16(sess->tpgt);
	fw_ddb_entry->mss = cpu_to_le16(conn->max_segment_size);
	fw_ddb_entry->tcp_xmt_wsf = (uint8_t) cpu_to_le32(conn->tcp_xmit_wsf);
	fw_ddb_entry->tcp_rcv_wsf = (uint8_t) cpu_to_le32(conn->tcp_recv_wsf);
	fw_ddb_entry->ipv6_flow_lbl = cpu_to_le16(conn->ipv6_flow_label);
	fw_ddb_entry->ka_timeout = cpu_to_le16(conn->keepalive_timeout);
	fw_ddb_entry->lcl_port = cpu_to_le16(conn->local_port);
	fw_ddb_entry->stat_sn = cpu_to_le32(conn->statsn);
	fw_ddb_entry->exp_stat_sn = cpu_to_le32(conn->exp_statsn);
	fw_ddb_entry->ddb_link = cpu_to_le16(sess->discovery_parent_idx);
	fw_ddb_entry->chap_tbl_idx = cpu_to_le16(sess->chap_out_idx);
	fw_ddb_entry->tsid = cpu_to_le16(sess->tsid);
	fw_ddb_entry->port = cpu_to_le16(conn->port);
	fw_ddb_entry->def_timeout =
				cpu_to_le16(sess->default_taskmgmt_timeout);

	if (!strncmp(sess->portal_type, PORTAL_TYPE_IPV6, 4))
		fw_ddb_entry->ipv4_tos = conn->ipv6_traffic_class;
	else
		fw_ddb_entry->ipv4_tos = conn->ipv4_tos;

	if (conn->ipaddress)
		memcpy(fw_ddb_entry->ip_addr, conn->ipaddress,
		       sizeof(fw_ddb_entry->ip_addr));

	if (conn->redirect_ipaddr)
		memcpy(fw_ddb_entry->tgt_addr, conn->redirect_ipaddr,
		       sizeof(fw_ddb_entry->tgt_addr));

	if (conn->link_local_ipv6_addr)
		memcpy(fw_ddb_entry->link_local_ipv6_addr,
		       conn->link_local_ipv6_addr,
		       sizeof(fw_ddb_entry->link_local_ipv6_addr));

	if (sess->targetname)
		memcpy(fw_ddb_entry->iscsi_name, sess->targetname,
		       sizeof(fw_ddb_entry->iscsi_name));

	if (sess->targetalias)
		memcpy(fw_ddb_entry->iscsi_alias, sess->targetalias,
		       sizeof(fw_ddb_entry->iscsi_alias));

	COPY_ISID(fw_ddb_entry->isid, sess->isid);

	return rc;
}
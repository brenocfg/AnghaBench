#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct mwifiex_private {TYPE_6__* adapter; int /*<<< orphan*/  bss_mode; int /*<<< orphan*/  tx_rate; } ;
struct mwifiex_hs_config_param {int dummy; } ;
struct host_cmd_ds_wmm_get_status {int dummy; } ;
struct host_cmd_ds_version_ext {int dummy; } ;
struct host_cmd_ds_tx_rate_query {int dummy; } ;
struct host_cmd_ds_set_bss_mode {int dummy; } ;
struct host_cmd_ds_remain_on_chan {int dummy; } ;
struct host_cmd_ds_pkt_aggr_ctrl {int dummy; } ;
struct host_cmd_ds_p2p_mode_cfg {int dummy; } ;
struct host_cmd_ds_mgmt_frame_reg {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  con_type; } ;
struct TYPE_10__ {void* mode; void* action; } ;
struct TYPE_9__ {void* enable; void* action; } ;
struct TYPE_8__ {int /*<<< orphan*/  mask; void* action; } ;
struct TYPE_12__ {int /*<<< orphan*/  version_str_sel; } ;
struct TYPE_14__ {TYPE_4__ bss_mode; TYPE_3__ mode_cfg; TYPE_2__ pkt_aggr_ctrl; TYPE_1__ reg_mask; TYPE_5__ verext; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_7__ params; } ;
struct TYPE_13__ {int /*<<< orphan*/  hw_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CONNECTION_TYPE_ADHOC ; 
 int /*<<< orphan*/  CONNECTION_TYPE_AP ; 
 int /*<<< orphan*/  CONNECTION_TYPE_INFRA ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ERROR ; 
#define  HostCmd_CMD_11AC_CFG 192 
#define  HostCmd_CMD_11N_ADDBA_REQ 191 
#define  HostCmd_CMD_11N_ADDBA_RSP 190 
#define  HostCmd_CMD_11N_CFG 189 
#define  HostCmd_CMD_11N_DELBA 188 
#define  HostCmd_CMD_802_11D_DOMAIN_INFO 187 
#define  HostCmd_CMD_802_11_AD_HOC_JOIN 186 
#define  HostCmd_CMD_802_11_AD_HOC_START 185 
#define  HostCmd_CMD_802_11_AD_HOC_STOP 184 
#define  HostCmd_CMD_802_11_ASSOCIATE 183 
#define  HostCmd_CMD_802_11_BG_SCAN_CONFIG 182 
#define  HostCmd_CMD_802_11_BG_SCAN_QUERY 181 
#define  HostCmd_CMD_802_11_DEAUTHENTICATE 180 
#define  HostCmd_CMD_802_11_EEPROM_ACCESS 179 
#define  HostCmd_CMD_802_11_GET_LOG 178 
#define  HostCmd_CMD_802_11_HS_CFG_ENH 177 
#define  HostCmd_CMD_802_11_IBSS_COALESCING_STATUS 176 
#define  HostCmd_CMD_802_11_KEY_MATERIAL 175 
#define  HostCmd_CMD_802_11_MAC_ADDRESS 174 
#define  HostCmd_CMD_802_11_PS_MODE_ENH 173 
#define  HostCmd_CMD_802_11_SCAN 172 
#define  HostCmd_CMD_802_11_SCAN_EXT 171 
#define  HostCmd_CMD_802_11_SNMP_MIB 170 
#define  HostCmd_CMD_802_11_SUBSCRIBE_EVENT 169 
#define  HostCmd_CMD_802_11_TX_RATE_QUERY 168 
#define  HostCmd_CMD_AMSDU_AGGR_CTRL 167 
#define  HostCmd_CMD_BBP_REG_ACCESS 166 
#define  HostCmd_CMD_CAU_REG_ACCESS 165 
#define  HostCmd_CMD_CFG_DATA 164 
#define  HostCmd_CMD_CHAN_REGION_CFG 163 
#define  HostCmd_CMD_CHAN_REPORT_REQUEST 162 
#define  HostCmd_CMD_COALESCE_CFG 161 
#define  HostCmd_CMD_FUNC_INIT 160 
#define  HostCmd_CMD_FUNC_SHUTDOWN 159 
#define  HostCmd_CMD_FW_DUMP_EVENT 158 
#define  HostCmd_CMD_GET_HW_SPEC 157 
#define  HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG 156 
#define  HostCmd_CMD_HS_WAKEUP_REASON 155 
#define  HostCmd_CMD_MAC_CONTROL 154 
#define  HostCmd_CMD_MAC_MULTICAST_ADR 153 
#define  HostCmd_CMD_MAC_REG_ACCESS 152 
#define  HostCmd_CMD_MC_POLICY 151 
#define  HostCmd_CMD_MEF_CFG 150 
#define  HostCmd_CMD_MEM_ACCESS 149 
#define  HostCmd_CMD_MGMT_FRAME_REG 148 
#define  HostCmd_CMD_P2P_MODE_CFG 147 
#define  HostCmd_CMD_PACKET_AGGR_CTRL 146 
#define  HostCmd_CMD_PCIE_DESC_DETAILS 145 
#define  HostCmd_CMD_PMIC_REG_ACCESS 144 
#define  HostCmd_CMD_RECONFIGURE_TX_BUFF 143 
#define  HostCmd_CMD_REMAIN_ON_CHAN 142 
#define  HostCmd_CMD_RF_ANTENNA 141 
#define  HostCmd_CMD_RF_REG_ACCESS 140 
#define  HostCmd_CMD_RF_TX_PWR 139 
#define  HostCmd_CMD_ROBUST_COEX 138 
#define  HostCmd_CMD_RSSI_INFO 137 
#define  HostCmd_CMD_SDIO_SP_RX_AGGR_CFG 136 
#define  HostCmd_CMD_SET_BSS_MODE 135 
#define  HostCmd_CMD_STA_CONFIGURE 134 
#define  HostCmd_CMD_TDLS_CONFIG 133 
#define  HostCmd_CMD_TDLS_OPER 132 
#define  HostCmd_CMD_TXPWR_CFG 131 
#define  HostCmd_CMD_TX_RATE_CFG 130 
#define  HostCmd_CMD_VERSION_EXT 129 
#define  HostCmd_CMD_WMM_GET_STATUS 128 
 int /*<<< orphan*/  MWIFIEX_HW_STATUS_READY ; 
 int /*<<< orphan*/  MWIFIEX_HW_STATUS_RESET ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_CLIENT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int S_DS_GEN ; 
 void* cpu_to_le16 (int const) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int get_unaligned (int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,void*,int) ; 
 int mwifiex_cmd_11ac_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_11n_addba_req (struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_11n_addba_rsp_gen (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_11n_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_11n_delba (struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_ad_hoc_join (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_ad_hoc_start (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_ad_hoc_stop (struct host_cmd_ds_command*) ; 
 int mwifiex_cmd_802_11_associate (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_bg_scan_config (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_bg_scan_query (struct host_cmd_ds_command*) ; 
 int mwifiex_cmd_802_11_deauthenticate (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_get_log (struct host_cmd_ds_command*) ; 
 int mwifiex_cmd_802_11_hs_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,int,struct mwifiex_hs_config_param*) ; 
 int mwifiex_cmd_802_11_key_material (struct mwifiex_private*,struct host_cmd_ds_command*,int,int,void*) ; 
 int mwifiex_cmd_802_11_mac_address (struct mwifiex_private*,struct host_cmd_ds_command*,int) ; 
 int mwifiex_cmd_802_11_rssi_info (struct mwifiex_private*,struct host_cmd_ds_command*,int) ; 
 int mwifiex_cmd_802_11_scan (struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_scan_ext (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11_snmp_mib (struct mwifiex_private*,struct host_cmd_ds_command*,int,int,void*) ; 
 int mwifiex_cmd_802_11_subsc_evt (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_802_11d_domain_info (struct mwifiex_private*,struct host_cmd_ds_command*,int) ; 
 int mwifiex_cmd_amsdu_aggr_ctrl (struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_cfg_data (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_chan_region_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,int) ; 
 int mwifiex_cmd_coalesce_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_enh_power_mode (struct mwifiex_private*,struct host_cmd_ds_command*,int,int,void*) ; 
 int mwifiex_cmd_get_chan_info (struct host_cmd_ds_command*,int) ; 
 int mwifiex_cmd_get_hw_spec (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_cmd_get_wakeup_reason (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_cmd_gtk_rekey_offload (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_ibss_coalescing_status (struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_issue_chan_report_request (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_mac_control (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_mac_multicast_adr (struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_mef_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_mem_access (struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_pcie_host_spec (struct mwifiex_private*,struct host_cmd_ds_command*,int) ; 
 int mwifiex_cmd_recfg_tx_buf (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_reg_access (struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_rf_antenna (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_rf_tx_power (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_robust_coex (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_sdio_rx_aggr_cfg (struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_set_mc_policy (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_tdls_config (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_tdls_oper (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_cmd_tx_power_cfg (struct host_cmd_ds_command*,int,void*) ; 
 int mwifiex_cmd_tx_rate_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,int,void*) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_is_cmd_supported (struct mwifiex_private*,int) ; 

int mwifiex_sta_prepare_cmd(struct mwifiex_private *priv, uint16_t cmd_no,
			    u16 cmd_action, u32 cmd_oid,
			    void *data_buf, void *cmd_buf)
{
	struct host_cmd_ds_command *cmd_ptr = cmd_buf;
	int ret = 0;

	if (mwifiex_is_cmd_supported(priv, cmd_no)) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "0x%x command not supported by firmware\n",
			    cmd_no);
		return -EOPNOTSUPP;
	}

	/* Prepare command */
	switch (cmd_no) {
	case HostCmd_CMD_GET_HW_SPEC:
		ret = mwifiex_cmd_get_hw_spec(priv, cmd_ptr);
		break;
	case HostCmd_CMD_CFG_DATA:
		ret = mwifiex_cmd_cfg_data(priv, cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_MAC_CONTROL:
		ret = mwifiex_cmd_mac_control(priv, cmd_ptr, cmd_action,
					      data_buf);
		break;
	case HostCmd_CMD_802_11_MAC_ADDRESS:
		ret = mwifiex_cmd_802_11_mac_address(priv, cmd_ptr,
						     cmd_action);
		break;
	case HostCmd_CMD_MAC_MULTICAST_ADR:
		ret = mwifiex_cmd_mac_multicast_adr(cmd_ptr, cmd_action,
						    data_buf);
		break;
	case HostCmd_CMD_TX_RATE_CFG:
		ret = mwifiex_cmd_tx_rate_cfg(priv, cmd_ptr, cmd_action,
					      data_buf);
		break;
	case HostCmd_CMD_TXPWR_CFG:
		ret = mwifiex_cmd_tx_power_cfg(cmd_ptr, cmd_action,
					       data_buf);
		break;
	case HostCmd_CMD_RF_TX_PWR:
		ret = mwifiex_cmd_rf_tx_power(priv, cmd_ptr, cmd_action,
					      data_buf);
		break;
	case HostCmd_CMD_RF_ANTENNA:
		ret = mwifiex_cmd_rf_antenna(priv, cmd_ptr, cmd_action,
					     data_buf);
		break;
	case HostCmd_CMD_802_11_PS_MODE_ENH:
		ret = mwifiex_cmd_enh_power_mode(priv, cmd_ptr, cmd_action,
						 (uint16_t)cmd_oid, data_buf);
		break;
	case HostCmd_CMD_802_11_HS_CFG_ENH:
		ret = mwifiex_cmd_802_11_hs_cfg(priv, cmd_ptr, cmd_action,
				(struct mwifiex_hs_config_param *) data_buf);
		break;
	case HostCmd_CMD_802_11_SCAN:
		ret = mwifiex_cmd_802_11_scan(cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_802_11_BG_SCAN_CONFIG:
		ret = mwifiex_cmd_802_11_bg_scan_config(priv, cmd_ptr,
							data_buf);
		break;
	case HostCmd_CMD_802_11_BG_SCAN_QUERY:
		ret = mwifiex_cmd_802_11_bg_scan_query(cmd_ptr);
		break;
	case HostCmd_CMD_802_11_ASSOCIATE:
		ret = mwifiex_cmd_802_11_associate(priv, cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_802_11_DEAUTHENTICATE:
		ret = mwifiex_cmd_802_11_deauthenticate(priv, cmd_ptr,
							data_buf);
		break;
	case HostCmd_CMD_802_11_AD_HOC_START:
		ret = mwifiex_cmd_802_11_ad_hoc_start(priv, cmd_ptr,
						      data_buf);
		break;
	case HostCmd_CMD_802_11_GET_LOG:
		ret = mwifiex_cmd_802_11_get_log(cmd_ptr);
		break;
	case HostCmd_CMD_802_11_AD_HOC_JOIN:
		ret = mwifiex_cmd_802_11_ad_hoc_join(priv, cmd_ptr,
						     data_buf);
		break;
	case HostCmd_CMD_802_11_AD_HOC_STOP:
		ret = mwifiex_cmd_802_11_ad_hoc_stop(cmd_ptr);
		break;
	case HostCmd_CMD_RSSI_INFO:
		ret = mwifiex_cmd_802_11_rssi_info(priv, cmd_ptr, cmd_action);
		break;
	case HostCmd_CMD_802_11_SNMP_MIB:
		ret = mwifiex_cmd_802_11_snmp_mib(priv, cmd_ptr, cmd_action,
						  cmd_oid, data_buf);
		break;
	case HostCmd_CMD_802_11_TX_RATE_QUERY:
		cmd_ptr->command =
			cpu_to_le16(HostCmd_CMD_802_11_TX_RATE_QUERY);
		cmd_ptr->size =
			cpu_to_le16(sizeof(struct host_cmd_ds_tx_rate_query) +
				    S_DS_GEN);
		priv->tx_rate = 0;
		ret = 0;
		break;
	case HostCmd_CMD_VERSION_EXT:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.verext.version_str_sel =
			(u8)(get_unaligned((u32 *)data_buf));
		memcpy(&cmd_ptr->params, data_buf,
		       sizeof(struct host_cmd_ds_version_ext));
		cmd_ptr->size =
			cpu_to_le16(sizeof(struct host_cmd_ds_version_ext) +
				    S_DS_GEN);
		ret = 0;
		break;
	case HostCmd_CMD_MGMT_FRAME_REG:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.reg_mask.action = cpu_to_le16(cmd_action);
		cmd_ptr->params.reg_mask.mask = cpu_to_le32(
						get_unaligned((u32 *)data_buf));
		cmd_ptr->size =
			cpu_to_le16(sizeof(struct host_cmd_ds_mgmt_frame_reg) +
				    S_DS_GEN);
		ret = 0;
		break;
	case HostCmd_CMD_REMAIN_ON_CHAN:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		memcpy(&cmd_ptr->params, data_buf,
		       sizeof(struct host_cmd_ds_remain_on_chan));
		cmd_ptr->size =
		      cpu_to_le16(sizeof(struct host_cmd_ds_remain_on_chan) +
				  S_DS_GEN);
		break;
	case HostCmd_CMD_11AC_CFG:
		ret = mwifiex_cmd_11ac_cfg(priv, cmd_ptr, cmd_action, data_buf);
		break;
	case HostCmd_CMD_PACKET_AGGR_CTRL:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.pkt_aggr_ctrl.action = cpu_to_le16(cmd_action);
		cmd_ptr->params.pkt_aggr_ctrl.enable =
						cpu_to_le16(*(u16 *)data_buf);
		cmd_ptr->size =
			cpu_to_le16(sizeof(struct host_cmd_ds_pkt_aggr_ctrl) +
				    S_DS_GEN);
		break;
	case HostCmd_CMD_P2P_MODE_CFG:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.mode_cfg.action = cpu_to_le16(cmd_action);
		cmd_ptr->params.mode_cfg.mode = cpu_to_le16(
						get_unaligned((u16 *)data_buf));
		cmd_ptr->size =
			cpu_to_le16(sizeof(struct host_cmd_ds_p2p_mode_cfg) +
				    S_DS_GEN);
		break;
	case HostCmd_CMD_FUNC_INIT:
		if (priv->adapter->hw_status == MWIFIEX_HW_STATUS_RESET)
			priv->adapter->hw_status = MWIFIEX_HW_STATUS_READY;
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->size = cpu_to_le16(S_DS_GEN);
		break;
	case HostCmd_CMD_FUNC_SHUTDOWN:
		priv->adapter->hw_status = MWIFIEX_HW_STATUS_RESET;
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->size = cpu_to_le16(S_DS_GEN);
		break;
	case HostCmd_CMD_11N_ADDBA_REQ:
		ret = mwifiex_cmd_11n_addba_req(cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_11N_DELBA:
		ret = mwifiex_cmd_11n_delba(cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_11N_ADDBA_RSP:
		ret = mwifiex_cmd_11n_addba_rsp_gen(priv, cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_802_11_KEY_MATERIAL:
		ret = mwifiex_cmd_802_11_key_material(priv, cmd_ptr,
						      cmd_action, cmd_oid,
						      data_buf);
		break;
	case HostCmd_CMD_802_11D_DOMAIN_INFO:
		ret = mwifiex_cmd_802_11d_domain_info(priv, cmd_ptr,
						      cmd_action);
		break;
	case HostCmd_CMD_RECONFIGURE_TX_BUFF:
		ret = mwifiex_cmd_recfg_tx_buf(priv, cmd_ptr, cmd_action,
					       data_buf);
		break;
	case HostCmd_CMD_AMSDU_AGGR_CTRL:
		ret = mwifiex_cmd_amsdu_aggr_ctrl(cmd_ptr, cmd_action,
						  data_buf);
		break;
	case HostCmd_CMD_11N_CFG:
		ret = mwifiex_cmd_11n_cfg(priv, cmd_ptr, cmd_action, data_buf);
		break;
	case HostCmd_CMD_WMM_GET_STATUS:
		mwifiex_dbg(priv->adapter, CMD,
			    "cmd: WMM: WMM_GET_STATUS cmd sent\n");
		cmd_ptr->command = cpu_to_le16(HostCmd_CMD_WMM_GET_STATUS);
		cmd_ptr->size =
			cpu_to_le16(sizeof(struct host_cmd_ds_wmm_get_status) +
				    S_DS_GEN);
		ret = 0;
		break;
	case HostCmd_CMD_802_11_IBSS_COALESCING_STATUS:
		ret = mwifiex_cmd_ibss_coalescing_status(cmd_ptr, cmd_action,
							 data_buf);
		break;
	case HostCmd_CMD_802_11_SCAN_EXT:
		ret = mwifiex_cmd_802_11_scan_ext(priv, cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_MEM_ACCESS:
		ret = mwifiex_cmd_mem_access(cmd_ptr, cmd_action, data_buf);
		break;
	case HostCmd_CMD_MAC_REG_ACCESS:
	case HostCmd_CMD_BBP_REG_ACCESS:
	case HostCmd_CMD_RF_REG_ACCESS:
	case HostCmd_CMD_PMIC_REG_ACCESS:
	case HostCmd_CMD_CAU_REG_ACCESS:
	case HostCmd_CMD_802_11_EEPROM_ACCESS:
		ret = mwifiex_cmd_reg_access(cmd_ptr, cmd_action, data_buf);
		break;
	case HostCmd_CMD_SET_BSS_MODE:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		if (priv->bss_mode == NL80211_IFTYPE_ADHOC)
			cmd_ptr->params.bss_mode.con_type =
				CONNECTION_TYPE_ADHOC;
		else if (priv->bss_mode == NL80211_IFTYPE_STATION ||
			 priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT)
			cmd_ptr->params.bss_mode.con_type =
				CONNECTION_TYPE_INFRA;
		else if (priv->bss_mode == NL80211_IFTYPE_AP ||
			 priv->bss_mode == NL80211_IFTYPE_P2P_GO)
			cmd_ptr->params.bss_mode.con_type = CONNECTION_TYPE_AP;
		cmd_ptr->size = cpu_to_le16(sizeof(struct
				host_cmd_ds_set_bss_mode) + S_DS_GEN);
		ret = 0;
		break;
	case HostCmd_CMD_PCIE_DESC_DETAILS:
		ret = mwifiex_cmd_pcie_host_spec(priv, cmd_ptr, cmd_action);
		break;
	case HostCmd_CMD_802_11_SUBSCRIBE_EVENT:
		ret = mwifiex_cmd_802_11_subsc_evt(priv, cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_MEF_CFG:
		ret = mwifiex_cmd_mef_cfg(priv, cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_COALESCE_CFG:
		ret = mwifiex_cmd_coalesce_cfg(priv, cmd_ptr, cmd_action,
					       data_buf);
		break;
	case HostCmd_CMD_TDLS_OPER:
		ret = mwifiex_cmd_tdls_oper(priv, cmd_ptr, data_buf);
		break;
	case HostCmd_CMD_TDLS_CONFIG:
		ret = mwifiex_cmd_tdls_config(priv, cmd_ptr, cmd_action,
					      data_buf);
		break;
	case HostCmd_CMD_CHAN_REPORT_REQUEST:
		ret = mwifiex_cmd_issue_chan_report_request(priv, cmd_ptr,
							    data_buf);
		break;
	case HostCmd_CMD_SDIO_SP_RX_AGGR_CFG:
		ret = mwifiex_cmd_sdio_rx_aggr_cfg(cmd_ptr, cmd_action,
						   data_buf);
		break;
	case HostCmd_CMD_HS_WAKEUP_REASON:
		ret = mwifiex_cmd_get_wakeup_reason(priv, cmd_ptr);
		break;
	case HostCmd_CMD_MC_POLICY:
		ret = mwifiex_cmd_set_mc_policy(priv, cmd_ptr, cmd_action,
						data_buf);
		break;
	case HostCmd_CMD_ROBUST_COEX:
		ret = mwifiex_cmd_robust_coex(priv, cmd_ptr, cmd_action,
					      data_buf);
		break;
	case HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG:
		ret = mwifiex_cmd_gtk_rekey_offload(priv, cmd_ptr, cmd_action,
						    data_buf);
		break;
	case HostCmd_CMD_CHAN_REGION_CFG:
		ret = mwifiex_cmd_chan_region_cfg(priv, cmd_ptr, cmd_action);
		break;
	case HostCmd_CMD_FW_DUMP_EVENT:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->size = cpu_to_le16(S_DS_GEN);
		break;
	case HostCmd_CMD_STA_CONFIGURE:
		ret = mwifiex_cmd_get_chan_info(cmd_ptr, cmd_action);
		break;
	default:
		mwifiex_dbg(priv->adapter, ERROR,
			    "PREP_CMD: unknown cmd- %#x\n", cmd_no);
		ret = -1;
		break;
	}
	return ret;
}
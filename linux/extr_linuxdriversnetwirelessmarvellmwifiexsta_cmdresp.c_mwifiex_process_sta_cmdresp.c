#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/  wiphy; } ;
struct mwifiex_private {int bss_started; TYPE_2__ wdev; struct mwifiex_adapter* adapter; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* update_mp_end_port ) (struct mwifiex_adapter*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* multi_port_resync ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {int usb_mc_setup; int tx_lock_flag; int tx_buf_size; int curr_tx_buf_size; int pps_uapsd_mode; int delay_null_pkt; TYPE_3__ if_ops; int /*<<< orphan*/  iface_type; TYPE_1__* curr_cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  mp_end_port; int /*<<< orphan*/  buff_size; } ;
struct TYPE_10__ {TYPE_4__ tx_buf; } ;
struct host_cmd_ds_command {scalar_t__ result; int command; TYPE_5__ params; } ;
struct TYPE_6__ {int wait_q_enabled; void* data_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  ERROR ; 
#define  HOST_CMD_APCMD_STA_LIST 197 
#define  HOST_CMD_APCMD_SYS_RESET 196 
#define  HostCmd_CMD_11AC_CFG 195 
#define  HostCmd_CMD_11N_ADDBA_REQ 194 
#define  HostCmd_CMD_11N_ADDBA_RSP 193 
#define  HostCmd_CMD_11N_CFG 192 
#define  HostCmd_CMD_11N_DELBA 191 
#define  HostCmd_CMD_802_11D_DOMAIN_INFO 190 
#define  HostCmd_CMD_802_11_AD_HOC_JOIN 189 
#define  HostCmd_CMD_802_11_AD_HOC_START 188 
#define  HostCmd_CMD_802_11_AD_HOC_STOP 187 
#define  HostCmd_CMD_802_11_ASSOCIATE 186 
#define  HostCmd_CMD_802_11_BG_SCAN_CONFIG 185 
#define  HostCmd_CMD_802_11_BG_SCAN_QUERY 184 
#define  HostCmd_CMD_802_11_DEAUTHENTICATE 183 
#define  HostCmd_CMD_802_11_EEPROM_ACCESS 182 
#define  HostCmd_CMD_802_11_GET_LOG 181 
#define  HostCmd_CMD_802_11_HS_CFG_ENH 180 
#define  HostCmd_CMD_802_11_IBSS_COALESCING_STATUS 179 
#define  HostCmd_CMD_802_11_KEY_MATERIAL 178 
#define  HostCmd_CMD_802_11_MAC_ADDRESS 177 
#define  HostCmd_CMD_802_11_PS_MODE_ENH 176 
#define  HostCmd_CMD_802_11_SCAN 175 
#define  HostCmd_CMD_802_11_SCAN_EXT 174 
#define  HostCmd_CMD_802_11_SNMP_MIB 173 
#define  HostCmd_CMD_802_11_SUBSCRIBE_EVENT 172 
#define  HostCmd_CMD_802_11_TX_RATE_QUERY 171 
#define  HostCmd_CMD_AMSDU_AGGR_CTRL 170 
#define  HostCmd_CMD_BBP_REG_ACCESS 169 
#define  HostCmd_CMD_CAU_REG_ACCESS 168 
#define  HostCmd_CMD_CFG_DATA 167 
#define  HostCmd_CMD_CHAN_REGION_CFG 166 
#define  HostCmd_CMD_CHAN_REPORT_REQUEST 165 
#define  HostCmd_CMD_COALESCE_CFG 164 
#define  HostCmd_CMD_FUNC_INIT 163 
#define  HostCmd_CMD_FUNC_SHUTDOWN 162 
#define  HostCmd_CMD_GET_HW_SPEC 161 
#define  HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG 160 
#define  HostCmd_CMD_HS_WAKEUP_REASON 159 
#define  HostCmd_CMD_MAC_CONTROL 158 
#define  HostCmd_CMD_MAC_MULTICAST_ADR 157 
#define  HostCmd_CMD_MAC_REG_ACCESS 156 
#define  HostCmd_CMD_MC_POLICY 155 
#define  HostCmd_CMD_MEF_CFG 154 
#define  HostCmd_CMD_MEM_ACCESS 153 
#define  HostCmd_CMD_MGMT_FRAME_REG 152 
#define  HostCmd_CMD_P2P_MODE_CFG 151 
#define  HostCmd_CMD_PACKET_AGGR_CTRL 150 
#define  HostCmd_CMD_PCIE_DESC_DETAILS 149 
#define  HostCmd_CMD_PMIC_REG_ACCESS 148 
#define  HostCmd_CMD_RECONFIGURE_TX_BUFF 147 
#define  HostCmd_CMD_REMAIN_ON_CHAN 146 
#define  HostCmd_CMD_RF_ANTENNA 145 
#define  HostCmd_CMD_RF_REG_ACCESS 144 
#define  HostCmd_CMD_RF_TX_PWR 143 
#define  HostCmd_CMD_ROBUST_COEX 142 
#define  HostCmd_CMD_RSSI_INFO 141 
#define  HostCmd_CMD_SDIO_SP_RX_AGGR_CFG 140 
#define  HostCmd_CMD_SET_BSS_MODE 139 
#define  HostCmd_CMD_STA_CONFIGURE 138 
#define  HostCmd_CMD_TDLS_CONFIG 137 
#define  HostCmd_CMD_TDLS_OPER 136 
#define  HostCmd_CMD_TXPWR_CFG 135 
#define  HostCmd_CMD_TX_RATE_CFG 134 
#define  HostCmd_CMD_UAP_BSS_START 133 
#define  HostCmd_CMD_UAP_BSS_STOP 132 
#define  HostCmd_CMD_UAP_STA_DEAUTH 131 
#define  HostCmd_CMD_UAP_SYS_CONFIG 130 
#define  HostCmd_CMD_VERSION_EXT 129 
#define  HostCmd_CMD_WMM_GET_STATUS 128 
 scalar_t__ HostCmd_RESULT_OK ; 
 int MWIFIEX_SDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  MWIFIEX_USB ; 
 int /*<<< orphan*/  cfg80211_sched_scan_results (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_process_cmdresp_error (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_11n_addba_req (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_11n_addba_resp (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_11n_delba (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_ad_hoc (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_ad_hoc_stop (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_associate (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_deauthenticate (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_hs_cfg (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_key_material (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_mac_address (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_rssi_info (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_scan (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_scan_ext (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11_snmp_mib (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_802_11_tx_rate_query (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_802_11d_domain_info (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_cfg_data (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_chan_region_cfg (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_enh_power_mode (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_get_chan_info (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_get_hw_spec (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_get_log (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_ibss_coalescing_status (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_mac_multicast_adr (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_mem_access (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_p2p_mode_cfg (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_pkt_aggr_ctrl (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_reg_access (int,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_remain_on_chan (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_rf_antenna (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_rf_tx_power (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_robust_coex (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_sdio_rx_aggr_cfg (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_subsc_evt (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_tdls_oper (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_tx_power_cfg (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_tx_rate_cfg (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_uap_sta_list (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int mwifiex_ret_ver_ext (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_wakeup_reason (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int mwifiex_ret_wmm_get_status (struct mwifiex_private*,struct host_cmd_ds_command*) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  stub2 (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 

int mwifiex_process_sta_cmdresp(struct mwifiex_private *priv, u16 cmdresp_no,
				struct host_cmd_ds_command *resp)
{
	int ret = 0;
	struct mwifiex_adapter *adapter = priv->adapter;
	void *data_buf = adapter->curr_cmd->data_buf;

	/* If the command is not successful, cleanup and return failure */
	if (resp->result != HostCmd_RESULT_OK) {
		mwifiex_process_cmdresp_error(priv, resp);
		return -1;
	}
	/* Command successful, handle response */
	switch (cmdresp_no) {
	case HostCmd_CMD_GET_HW_SPEC:
		ret = mwifiex_ret_get_hw_spec(priv, resp);
		break;
	case HostCmd_CMD_CFG_DATA:
		ret = mwifiex_ret_cfg_data(priv, resp);
		break;
	case HostCmd_CMD_MAC_CONTROL:
		break;
	case HostCmd_CMD_802_11_MAC_ADDRESS:
		ret = mwifiex_ret_802_11_mac_address(priv, resp);
		break;
	case HostCmd_CMD_MAC_MULTICAST_ADR:
		ret = mwifiex_ret_mac_multicast_adr(priv, resp);
		break;
	case HostCmd_CMD_TX_RATE_CFG:
		ret = mwifiex_ret_tx_rate_cfg(priv, resp);
		break;
	case HostCmd_CMD_802_11_SCAN:
		ret = mwifiex_ret_802_11_scan(priv, resp);
		adapter->curr_cmd->wait_q_enabled = false;
		break;
	case HostCmd_CMD_802_11_SCAN_EXT:
		ret = mwifiex_ret_802_11_scan_ext(priv, resp);
		adapter->curr_cmd->wait_q_enabled = false;
		break;
	case HostCmd_CMD_802_11_BG_SCAN_QUERY:
		ret = mwifiex_ret_802_11_scan(priv, resp);
		cfg80211_sched_scan_results(priv->wdev.wiphy, 0);
		mwifiex_dbg(adapter, CMD,
			    "info: CMD_RESP: BG_SCAN result is ready!\n");
		break;
	case HostCmd_CMD_802_11_BG_SCAN_CONFIG:
		break;
	case HostCmd_CMD_TXPWR_CFG:
		ret = mwifiex_ret_tx_power_cfg(priv, resp);
		break;
	case HostCmd_CMD_RF_TX_PWR:
		ret = mwifiex_ret_rf_tx_power(priv, resp);
		break;
	case HostCmd_CMD_RF_ANTENNA:
		ret = mwifiex_ret_rf_antenna(priv, resp);
		break;
	case HostCmd_CMD_802_11_PS_MODE_ENH:
		ret = mwifiex_ret_enh_power_mode(priv, resp, data_buf);
		break;
	case HostCmd_CMD_802_11_HS_CFG_ENH:
		ret = mwifiex_ret_802_11_hs_cfg(priv, resp);
		break;
	case HostCmd_CMD_802_11_ASSOCIATE:
		ret = mwifiex_ret_802_11_associate(priv, resp);
		break;
	case HostCmd_CMD_802_11_DEAUTHENTICATE:
		ret = mwifiex_ret_802_11_deauthenticate(priv, resp);
		break;
	case HostCmd_CMD_802_11_AD_HOC_START:
	case HostCmd_CMD_802_11_AD_HOC_JOIN:
		ret = mwifiex_ret_802_11_ad_hoc(priv, resp);
		break;
	case HostCmd_CMD_802_11_AD_HOC_STOP:
		ret = mwifiex_ret_802_11_ad_hoc_stop(priv, resp);
		break;
	case HostCmd_CMD_802_11_GET_LOG:
		ret = mwifiex_ret_get_log(priv, resp, data_buf);
		break;
	case HostCmd_CMD_RSSI_INFO:
		ret = mwifiex_ret_802_11_rssi_info(priv, resp);
		break;
	case HostCmd_CMD_802_11_SNMP_MIB:
		ret = mwifiex_ret_802_11_snmp_mib(priv, resp, data_buf);
		break;
	case HostCmd_CMD_802_11_TX_RATE_QUERY:
		ret = mwifiex_ret_802_11_tx_rate_query(priv, resp);
		break;
	case HostCmd_CMD_VERSION_EXT:
		ret = mwifiex_ret_ver_ext(priv, resp, data_buf);
		break;
	case HostCmd_CMD_REMAIN_ON_CHAN:
		ret = mwifiex_ret_remain_on_chan(priv, resp, data_buf);
		break;
	case HostCmd_CMD_11AC_CFG:
		break;
	case HostCmd_CMD_PACKET_AGGR_CTRL:
		ret = mwifiex_ret_pkt_aggr_ctrl(priv, resp);
		break;
	case HostCmd_CMD_P2P_MODE_CFG:
		ret = mwifiex_ret_p2p_mode_cfg(priv, resp, data_buf);
		break;
	case HostCmd_CMD_MGMT_FRAME_REG:
	case HostCmd_CMD_FUNC_INIT:
	case HostCmd_CMD_FUNC_SHUTDOWN:
		break;
	case HostCmd_CMD_802_11_KEY_MATERIAL:
		ret = mwifiex_ret_802_11_key_material(priv, resp);
		break;
	case HostCmd_CMD_802_11D_DOMAIN_INFO:
		ret = mwifiex_ret_802_11d_domain_info(priv, resp);
		break;
	case HostCmd_CMD_11N_ADDBA_REQ:
		ret = mwifiex_ret_11n_addba_req(priv, resp);
		break;
	case HostCmd_CMD_11N_DELBA:
		ret = mwifiex_ret_11n_delba(priv, resp);
		break;
	case HostCmd_CMD_11N_ADDBA_RSP:
		ret = mwifiex_ret_11n_addba_resp(priv, resp);
		break;
	case HostCmd_CMD_RECONFIGURE_TX_BUFF:
		if (0xffff == (u16)le16_to_cpu(resp->params.tx_buf.buff_size)) {
			if (adapter->iface_type == MWIFIEX_USB &&
			    adapter->usb_mc_setup) {
				if (adapter->if_ops.multi_port_resync)
					adapter->if_ops.
						multi_port_resync(adapter);
				adapter->usb_mc_setup = false;
				adapter->tx_lock_flag = false;
			}
			break;
		}
		adapter->tx_buf_size = (u16) le16_to_cpu(resp->params.
							     tx_buf.buff_size);
		adapter->tx_buf_size = (adapter->tx_buf_size
					/ MWIFIEX_SDIO_BLOCK_SIZE)
				       * MWIFIEX_SDIO_BLOCK_SIZE;
		adapter->curr_tx_buf_size = adapter->tx_buf_size;
		mwifiex_dbg(adapter, CMD, "cmd: curr_tx_buf_size=%d\n",
			    adapter->curr_tx_buf_size);

		if (adapter->if_ops.update_mp_end_port)
			adapter->if_ops.update_mp_end_port(adapter,
				le16_to_cpu(resp->params.tx_buf.mp_end_port));
		break;
	case HostCmd_CMD_AMSDU_AGGR_CTRL:
		break;
	case HostCmd_CMD_WMM_GET_STATUS:
		ret = mwifiex_ret_wmm_get_status(priv, resp);
		break;
	case HostCmd_CMD_802_11_IBSS_COALESCING_STATUS:
		ret = mwifiex_ret_ibss_coalescing_status(priv, resp);
		break;
	case HostCmd_CMD_MEM_ACCESS:
		ret = mwifiex_ret_mem_access(priv, resp, data_buf);
		break;
	case HostCmd_CMD_MAC_REG_ACCESS:
	case HostCmd_CMD_BBP_REG_ACCESS:
	case HostCmd_CMD_RF_REG_ACCESS:
	case HostCmd_CMD_PMIC_REG_ACCESS:
	case HostCmd_CMD_CAU_REG_ACCESS:
	case HostCmd_CMD_802_11_EEPROM_ACCESS:
		ret = mwifiex_ret_reg_access(cmdresp_no, resp, data_buf);
		break;
	case HostCmd_CMD_SET_BSS_MODE:
		break;
	case HostCmd_CMD_11N_CFG:
		break;
	case HostCmd_CMD_PCIE_DESC_DETAILS:
		break;
	case HostCmd_CMD_802_11_SUBSCRIBE_EVENT:
		ret = mwifiex_ret_subsc_evt(priv, resp);
		break;
	case HostCmd_CMD_UAP_SYS_CONFIG:
		break;
	case HOST_CMD_APCMD_STA_LIST:
		ret = mwifiex_ret_uap_sta_list(priv, resp);
		break;
	case HostCmd_CMD_UAP_BSS_START:
		adapter->tx_lock_flag = false;
		adapter->pps_uapsd_mode = false;
		adapter->delay_null_pkt = false;
		priv->bss_started = 1;
		break;
	case HostCmd_CMD_UAP_BSS_STOP:
		priv->bss_started = 0;
		break;
	case HostCmd_CMD_UAP_STA_DEAUTH:
		break;
	case HOST_CMD_APCMD_SYS_RESET:
		break;
	case HostCmd_CMD_MEF_CFG:
		break;
	case HostCmd_CMD_COALESCE_CFG:
		break;
	case HostCmd_CMD_TDLS_OPER:
		ret = mwifiex_ret_tdls_oper(priv, resp);
	case HostCmd_CMD_MC_POLICY:
		break;
	case HostCmd_CMD_CHAN_REPORT_REQUEST:
		break;
	case HostCmd_CMD_SDIO_SP_RX_AGGR_CFG:
		ret = mwifiex_ret_sdio_rx_aggr_cfg(priv, resp);
		break;
	case HostCmd_CMD_HS_WAKEUP_REASON:
		ret = mwifiex_ret_wakeup_reason(priv, resp, data_buf);
		break;
	case HostCmd_CMD_TDLS_CONFIG:
		break;
	case HostCmd_CMD_ROBUST_COEX:
		ret = mwifiex_ret_robust_coex(priv, resp, data_buf);
		break;
	case HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG:
		break;
	case HostCmd_CMD_CHAN_REGION_CFG:
		ret = mwifiex_ret_chan_region_cfg(priv, resp);
		break;
	case HostCmd_CMD_STA_CONFIGURE:
		ret = mwifiex_ret_get_chan_info(priv, resp, data_buf);
		break;
	default:
		mwifiex_dbg(adapter, ERROR,
			    "CMD_RESP: unknown cmd response %#x\n",
			    resp->command);
		break;
	}

	return ret;
}
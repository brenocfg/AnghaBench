#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  sta_id; } ;
struct TYPE_18__ {TYPE_3__ peer; } ;
struct TYPE_15__ {int /*<<< orphan*/  conf; } ;
struct TYPE_14__ {TYPE_1__ dump; } ;
struct iwl_mvm {int /*<<< orphan*/  status; void* hb_scan_type; void* scan_type; TYPE_8__* fw; int /*<<< orphan*/ * phy_ctxts; TYPE_7__* hw; int /*<<< orphan*/  last_quota_cmd; TYPE_4__ tdls_cs; int /*<<< orphan*/ * fw_id_to_mac_id; TYPE_10__* trans; int /*<<< orphan*/  phy_db; TYPE_11__ fwrt; int /*<<< orphan*/  mutex; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_23__ {int /*<<< orphan*/  init_dbg; } ;
struct TYPE_22__ {int /*<<< orphan*/  ucode_capa; scalar_t__ dbg_dest_tlv; } ;
struct TYPE_21__ {TYPE_6__* wiphy; } ;
struct TYPE_20__ {TYPE_5__** bands; } ;
struct TYPE_19__ {struct ieee80211_channel* channels; } ;
struct TYPE_16__ {scalar_t__ device_family; } ;
struct TYPE_13__ {TYPE_2__* cfg; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FW_DBG_INVALID ; 
 int /*<<< orphan*/  FW_DBG_START_FROM_ALIVE ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_REF_UCODE_DOWN ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_CTKILL ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 void* IWL_SCAN_TYPE_NOT_SET ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_UMAC_SCAN ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
 int NUM_PHY_CTX ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_configure_rxq (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_fw_start_dbg_conf (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_get_shared_mem_conf (TYPE_11__*) ; 
 int iwl_mvm_add_aux_sta (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_config_ltr (struct iwl_mvm*) ; 
 int iwl_mvm_config_scan (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_has_new_rx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_has_unified_ucode (struct iwl_mvm*) ; 
 int iwl_mvm_init_mcc (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_leds_sync (struct iwl_mvm*) ; 
 int iwl_mvm_load_rt_fw (struct iwl_mvm*) ; 
 int iwl_mvm_phy_ctxt_add (struct iwl_mvm*,int /*<<< orphan*/ *,struct cfg80211_chan_def*,int,int) ; 
 int iwl_mvm_power_update_device (struct iwl_mvm*) ; 
 int iwl_mvm_sar_geo_init (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_sar_get_wgds_table (struct iwl_mvm*) ; 
 int iwl_mvm_sar_init (struct iwl_mvm*) ; 
 int iwl_mvm_send_bt_init_conf (struct iwl_mvm*) ; 
 int iwl_mvm_send_dqa_cmd (struct iwl_mvm*) ; 
 int iwl_mvm_sf_update (struct iwl_mvm*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iwl_mvm_stop_device (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_tt_tx_backoff (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_send_phy_cfg_cmd (struct iwl_mvm*) ; 
 int iwl_send_phy_db_data (int /*<<< orphan*/ ) ; 
 int iwl_send_rss_cfg_cmd (struct iwl_mvm*) ; 
 int iwl_send_tx_ant_cfg (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_trans_start_hw (TYPE_10__*) ; 
 TYPE_9__ iwlmvm_mod_params ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_mvm_up(struct iwl_mvm *mvm)
{
	int ret, i;
	struct ieee80211_channel *chan;
	struct cfg80211_chan_def chandef;

	lockdep_assert_held(&mvm->mutex);

	ret = iwl_trans_start_hw(mvm->trans);
	if (ret)
		return ret;

	ret = iwl_mvm_load_rt_fw(mvm);
	if (ret) {
		IWL_ERR(mvm, "Failed to start RT ucode: %d\n", ret);
		goto error;
	}

	iwl_get_shared_mem_conf(&mvm->fwrt);

	ret = iwl_mvm_sf_update(mvm, NULL, false);
	if (ret)
		IWL_ERR(mvm, "Failed to initialize Smart Fifo\n");

	mvm->fwrt.dump.conf = FW_DBG_INVALID;
	/* if we have a destination, assume EARLY START */
	if (mvm->fw->dbg_dest_tlv)
		mvm->fwrt.dump.conf = FW_DBG_START_FROM_ALIVE;
	iwl_fw_start_dbg_conf(&mvm->fwrt, FW_DBG_START_FROM_ALIVE);

	ret = iwl_send_tx_ant_cfg(mvm, iwl_mvm_get_valid_tx_ant(mvm));
	if (ret)
		goto error;

	if (!iwl_mvm_has_unified_ucode(mvm)) {
		/* Send phy db control command and then phy db calibration */
		ret = iwl_send_phy_db_data(mvm->phy_db);
		if (ret)
			goto error;

		ret = iwl_send_phy_cfg_cmd(mvm);
		if (ret)
			goto error;
	}

	ret = iwl_mvm_send_bt_init_conf(mvm);
	if (ret)
		goto error;

	/* Init RSS configuration */
	if (mvm->trans->cfg->device_family >= IWL_DEVICE_FAMILY_22000) {
		ret = iwl_configure_rxq(mvm);
		if (ret) {
			IWL_ERR(mvm, "Failed to configure RX queues: %d\n",
				ret);
			goto error;
		}
	}

	if (iwl_mvm_has_new_rx_api(mvm)) {
		ret = iwl_send_rss_cfg_cmd(mvm);
		if (ret) {
			IWL_ERR(mvm, "Failed to configure RSS queues: %d\n",
				ret);
			goto error;
		}
	}

	/* init the fw <-> mac80211 STA mapping */
	for (i = 0; i < ARRAY_SIZE(mvm->fw_id_to_mac_id); i++)
		RCU_INIT_POINTER(mvm->fw_id_to_mac_id[i], NULL);

	mvm->tdls_cs.peer.sta_id = IWL_MVM_INVALID_STA;

	/* reset quota debouncing buffer - 0xff will yield invalid data */
	memset(&mvm->last_quota_cmd, 0xff, sizeof(mvm->last_quota_cmd));

	ret = iwl_mvm_send_dqa_cmd(mvm);
	if (ret)
		goto error;

	/* Add auxiliary station for scanning */
	ret = iwl_mvm_add_aux_sta(mvm);
	if (ret)
		goto error;

	/* Add all the PHY contexts */
	chan = &mvm->hw->wiphy->bands[NL80211_BAND_2GHZ]->channels[0];
	cfg80211_chandef_create(&chandef, chan, NL80211_CHAN_NO_HT);
	for (i = 0; i < NUM_PHY_CTX; i++) {
		/*
		 * The channel used here isn't relevant as it's
		 * going to be overwritten in the other flows.
		 * For now use the first channel we have.
		 */
		ret = iwl_mvm_phy_ctxt_add(mvm, &mvm->phy_ctxts[i],
					   &chandef, 1, 1);
		if (ret)
			goto error;
	}

#ifdef CONFIG_THERMAL
	if (iwl_mvm_is_tt_in_fw(mvm)) {
		/* in order to give the responsibility of ct-kill and
		 * TX backoff to FW we need to send empty temperature reporting
		 * cmd during init time
		 */
		iwl_mvm_send_temp_report_ths_cmd(mvm);
	} else {
		/* Initialize tx backoffs to the minimal possible */
		iwl_mvm_tt_tx_backoff(mvm, 0);
	}

	/* TODO: read the budget from BIOS / Platform NVM */

	/*
	 * In case there is no budget from BIOS / Platform NVM the default
	 * budget should be 2000mW (cooling state 0).
	 */
	if (iwl_mvm_is_ctdp_supported(mvm)) {
		ret = iwl_mvm_ctdp_command(mvm, CTDP_CMD_OPERATION_START,
					   mvm->cooling_dev.cur_state);
		if (ret)
			goto error;
	}
#else
	/* Initialize tx backoffs to the minimal possible */
	iwl_mvm_tt_tx_backoff(mvm, 0);
#endif

	WARN_ON(iwl_mvm_config_ltr(mvm));

	ret = iwl_mvm_power_update_device(mvm);
	if (ret)
		goto error;

	/*
	 * RTNL is not taken during Ct-kill, but we don't need to scan/Tx
	 * anyway, so don't init MCC.
	 */
	if (!test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status)) {
		ret = iwl_mvm_init_mcc(mvm);
		if (ret)
			goto error;
	}

	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN)) {
		mvm->scan_type = IWL_SCAN_TYPE_NOT_SET;
		mvm->hb_scan_type = IWL_SCAN_TYPE_NOT_SET;
		ret = iwl_mvm_config_scan(mvm);
		if (ret)
			goto error;
	}

	/* allow FW/transport low power modes if not during restart */
	if (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
		iwl_mvm_unref(mvm, IWL_MVM_REF_UCODE_DOWN);

	ret = iwl_mvm_sar_init(mvm);
	if (ret == 0) {
		ret = iwl_mvm_sar_geo_init(mvm);
	} else if (ret > 0 && !iwl_mvm_sar_get_wgds_table(mvm)) {
		/*
		 * If basic SAR is not available, we check for WGDS,
		 * which should *not* be available either.  If it is
		 * available, issue an error, because we can't use SAR
		 * Geo without basic SAR.
		 */
		IWL_ERR(mvm, "BIOS contains WGDS but no WRDS\n");
	}

	if (ret < 0)
		goto error;

	iwl_mvm_leds_sync(mvm);

	IWL_DEBUG_INFO(mvm, "RT uCode started.\n");
	return 0;
 error:
	if (!iwlmvm_mod_params.init_dbg || !ret)
		iwl_mvm_stop_device(mvm);
	return ret;
}
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
struct ath9k_hw_mci {int gpm_len; int gpm_idx; int update_2g5g; int config; int last_recovery; int query_bt; int need_flush_btinfo; int /*<<< orphan*/  unhalt_bt_gpm; void* bt_state; int /*<<< orphan*/  ready; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BTCOEX_CTRL ; 
 int AR_BTCOEX_CTRL_MCI_MODE_EN ; 
 int /*<<< orphan*/  AR_GLB_GPIO_CONTROL ; 
 int /*<<< orphan*/  AR_MCI_GPM_1 ; 
 int /*<<< orphan*/  AR_MCI_GPM_WRITE_PTR ; 
 int /*<<< orphan*/  AR_MCI_RX_LAST_SCHD_MSG_INDEX ; 
 int /*<<< orphan*/  AR_MCI_RX_REMOTE_SLEEP ; 
 int /*<<< orphan*/  AR_MCI_RX_STATUS ; 
 int ATH_MCI_CONFIG_DISABLE_FTP_STOMP ; 
 int ATH_MCI_CONFIG_MCI_OBS_GPIO ; 
 int ATH_MCI_CONFIG_MCI_OBS_MASK ; 
 int /*<<< orphan*/  MCI ; 
 void* MCI_BT_AWAKE ; 
 void* MCI_BT_SLEEP ; 
 int /*<<< orphan*/  MCI_GPM_COEX_QUERY_BT_TOPOLOGY ; 
 int MCI_RECOVERY_DUR_TSF ; 
#define  MCI_STATE_AIC_CAL 143 
#define  MCI_STATE_AIC_CAL_RESET 142 
#define  MCI_STATE_AIC_CAL_SINGLE 141 
#define  MCI_STATE_AIC_START 140 
#define  MCI_STATE_ENABLE 139 
#define  MCI_STATE_INIT_GPM_OFFSET 138 
#define  MCI_STATE_LAST_SCHD_MSG_OFFSET 137 
#define  MCI_STATE_NEED_FLUSH_BT_INFO 136 
#define  MCI_STATE_NEED_FTP_STOMP 135 
#define  MCI_STATE_RECOVER_RX 134 
#define  MCI_STATE_REMOTE_SLEEP 133 
#define  MCI_STATE_RESET_REQ_WAKE 132 
#define  MCI_STATE_SEND_STATUS_QUERY 131 
#define  MCI_STATE_SEND_VERSION_QUERY 130 
#define  MCI_STATE_SEND_WLAN_COEX_VERSION 129 
#define  MCI_STATE_SET_BT_AWAKE 128 
 int MS (int,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int ar9003_aic_cal_reset (struct ath_hw*) ; 
 int ar9003_aic_calibration (struct ath_hw*) ; 
 int ar9003_aic_calibration_single (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_aic_start_normal (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_2g5g_switch (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_observation_set_up (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_prep_interface (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_reset_req_wakeup (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_bt_status_query (struct ath_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_halt_bt_gpm (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_version_query (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_version_response (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_wlan_channels (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_hw_gettsf32 (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_is_aic_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

u32 ar9003_mci_state(struct ath_hw *ah, u32 state_type)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 value = 0, tsf;
	u8 query_type;

	switch (state_type) {
	case MCI_STATE_ENABLE:
		if (mci->ready) {
			value = REG_READ(ah, AR_BTCOEX_CTRL);

			if ((value == 0xdeadbeef) || (value == 0xffffffff))
				value = 0;
		}
		value &= AR_BTCOEX_CTRL_MCI_MODE_EN;
		break;
	case MCI_STATE_INIT_GPM_OFFSET:
		value = MS(REG_READ(ah, AR_MCI_GPM_1), AR_MCI_GPM_WRITE_PTR);

		if (value < mci->gpm_len)
			mci->gpm_idx = value;
		else
			mci->gpm_idx = 0;
		break;
	case MCI_STATE_LAST_SCHD_MSG_OFFSET:
		value = MS(REG_READ(ah, AR_MCI_RX_STATUS),
				    AR_MCI_RX_LAST_SCHD_MSG_INDEX);
		/* Make it in bytes */
		value <<= 4;
		break;
	case MCI_STATE_REMOTE_SLEEP:
		value = MS(REG_READ(ah, AR_MCI_RX_STATUS),
			   AR_MCI_RX_REMOTE_SLEEP) ?
			MCI_BT_SLEEP : MCI_BT_AWAKE;
		break;
	case MCI_STATE_SET_BT_AWAKE:
		mci->bt_state = MCI_BT_AWAKE;
		ar9003_mci_send_coex_version_query(ah, true);
		ar9003_mci_send_coex_wlan_channels(ah, true);

		if (mci->unhalt_bt_gpm)
			ar9003_mci_send_coex_halt_bt_gpm(ah, false, true);

		ar9003_mci_2g5g_switch(ah, false);
		break;
	case MCI_STATE_RESET_REQ_WAKE:
		ar9003_mci_reset_req_wakeup(ah);
		mci->update_2g5g = true;

		if (mci->config & ATH_MCI_CONFIG_MCI_OBS_MASK) {
			/* Check if we still have control of the GPIOs */
			if ((REG_READ(ah, AR_GLB_GPIO_CONTROL) &
			     ATH_MCI_CONFIG_MCI_OBS_GPIO) !=
			    ATH_MCI_CONFIG_MCI_OBS_GPIO) {
				ar9003_mci_observation_set_up(ah);
			}
		}
		break;
	case MCI_STATE_SEND_WLAN_COEX_VERSION:
		ar9003_mci_send_coex_version_response(ah, true);
		break;
	case MCI_STATE_SEND_VERSION_QUERY:
		ar9003_mci_send_coex_version_query(ah, true);
		break;
	case MCI_STATE_SEND_STATUS_QUERY:
		query_type = MCI_GPM_COEX_QUERY_BT_TOPOLOGY;
		ar9003_mci_send_coex_bt_status_query(ah, true, query_type);
		break;
	case MCI_STATE_RECOVER_RX:
		tsf = ath9k_hw_gettsf32(ah);
		if ((tsf - mci->last_recovery) <= MCI_RECOVERY_DUR_TSF) {
			ath_dbg(ath9k_hw_common(ah), MCI,
				"(MCI) ignore Rx recovery\n");
			break;
		}
		ath_dbg(ath9k_hw_common(ah), MCI, "(MCI) RECOVER RX\n");
		mci->last_recovery = tsf;
		ar9003_mci_prep_interface(ah);
		mci->query_bt = true;
		mci->need_flush_btinfo = true;
		ar9003_mci_send_coex_wlan_channels(ah, true);
		ar9003_mci_2g5g_switch(ah, false);
		break;
	case MCI_STATE_NEED_FTP_STOMP:
		value = !(mci->config & ATH_MCI_CONFIG_DISABLE_FTP_STOMP);
		break;
	case MCI_STATE_NEED_FLUSH_BT_INFO:
		value = (!mci->unhalt_bt_gpm && mci->need_flush_btinfo) ? 1 : 0;
		mci->need_flush_btinfo = false;
		break;
	case MCI_STATE_AIC_CAL:
		if (ath9k_hw_is_aic_enabled(ah))
			value = ar9003_aic_calibration(ah);
		break;
	case MCI_STATE_AIC_START:
		if (ath9k_hw_is_aic_enabled(ah))
			ar9003_aic_start_normal(ah);
		break;
	case MCI_STATE_AIC_CAL_RESET:
		if (ath9k_hw_is_aic_enabled(ah))
			value = ar9003_aic_cal_reset(ah);
		break;
	case MCI_STATE_AIC_CAL_SINGLE:
		if (ath9k_hw_is_aic_enabled(ah))
			value = ar9003_aic_calibration_single(ah);
		break;
	default:
		break;
	}

	return value;
}
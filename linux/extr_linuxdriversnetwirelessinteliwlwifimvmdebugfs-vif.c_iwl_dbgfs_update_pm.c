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
struct iwl_dbgfs_pm {int mask; int keep_alive_seconds; int skip_over_dtim; int skip_dtim_periods; int rx_data_timeout; int tx_data_timeout; int lprx_ena; int lprx_rssi_threshold; int snooze_ena; int uapsd_misbehaving; int use_ps_poll; } ;
struct iwl_mvm_vif {struct iwl_dbgfs_pm dbgfs_pm; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int beacon_int; int /*<<< orphan*/  dtim_period; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
typedef  enum iwl_dbgfs_pm_mask { ____Placeholder_iwl_dbgfs_pm_mask } iwl_dbgfs_pm_mask ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_POWER (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*,int,int) ; 
 int MSEC_PER_SEC ; 
#define  MVM_DEBUGFS_PM_KEEP_ALIVE 137 
#define  MVM_DEBUGFS_PM_LPRX_ENA 136 
#define  MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD 135 
#define  MVM_DEBUGFS_PM_RX_DATA_TIMEOUT 134 
#define  MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS 133 
#define  MVM_DEBUGFS_PM_SKIP_OVER_DTIM 132 
#define  MVM_DEBUGFS_PM_SNOOZE_ENABLE 131 
#define  MVM_DEBUGFS_PM_TX_DATA_TIMEOUT 130 
#define  MVM_DEBUGFS_PM_UAPSD_MISBEHAVING 129 
#define  MVM_DEBUGFS_PM_USE_PS_POLL 128 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_dbgfs_update_pm(struct iwl_mvm *mvm,
				 struct ieee80211_vif *vif,
				 enum iwl_dbgfs_pm_mask param, int val)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_dbgfs_pm *dbgfs_pm = &mvmvif->dbgfs_pm;

	dbgfs_pm->mask |= param;

	switch (param) {
	case MVM_DEBUGFS_PM_KEEP_ALIVE: {
		int dtimper = vif->bss_conf.dtim_period ?: 1;
		int dtimper_msec = dtimper * vif->bss_conf.beacon_int;

		IWL_DEBUG_POWER(mvm, "debugfs: set keep_alive= %d sec\n", val);
		if (val * MSEC_PER_SEC < 3 * dtimper_msec)
			IWL_WARN(mvm,
				 "debugfs: keep alive period (%ld msec) is less than minimum required (%d msec)\n",
				 val * MSEC_PER_SEC, 3 * dtimper_msec);
		dbgfs_pm->keep_alive_seconds = val;
		break;
	}
	case MVM_DEBUGFS_PM_SKIP_OVER_DTIM:
		IWL_DEBUG_POWER(mvm, "skip_over_dtim %s\n",
				val ? "enabled" : "disabled");
		dbgfs_pm->skip_over_dtim = val;
		break;
	case MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS:
		IWL_DEBUG_POWER(mvm, "skip_dtim_periods=%d\n", val);
		dbgfs_pm->skip_dtim_periods = val;
		break;
	case MVM_DEBUGFS_PM_RX_DATA_TIMEOUT:
		IWL_DEBUG_POWER(mvm, "rx_data_timeout=%d\n", val);
		dbgfs_pm->rx_data_timeout = val;
		break;
	case MVM_DEBUGFS_PM_TX_DATA_TIMEOUT:
		IWL_DEBUG_POWER(mvm, "tx_data_timeout=%d\n", val);
		dbgfs_pm->tx_data_timeout = val;
		break;
	case MVM_DEBUGFS_PM_LPRX_ENA:
		IWL_DEBUG_POWER(mvm, "lprx %s\n", val ? "enabled" : "disabled");
		dbgfs_pm->lprx_ena = val;
		break;
	case MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD:
		IWL_DEBUG_POWER(mvm, "lprx_rssi_threshold=%d\n", val);
		dbgfs_pm->lprx_rssi_threshold = val;
		break;
	case MVM_DEBUGFS_PM_SNOOZE_ENABLE:
		IWL_DEBUG_POWER(mvm, "snooze_enable=%d\n", val);
		dbgfs_pm->snooze_ena = val;
		break;
	case MVM_DEBUGFS_PM_UAPSD_MISBEHAVING:
		IWL_DEBUG_POWER(mvm, "uapsd_misbehaving_enable=%d\n", val);
		dbgfs_pm->uapsd_misbehaving = val;
		break;
	case MVM_DEBUGFS_PM_USE_PS_POLL:
		IWL_DEBUG_POWER(mvm, "use_ps_poll=%d\n", val);
		dbgfs_pm->use_ps_poll = val;
		break;
	}
}
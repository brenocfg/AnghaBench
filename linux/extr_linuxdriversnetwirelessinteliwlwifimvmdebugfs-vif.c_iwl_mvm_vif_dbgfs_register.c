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
struct iwl_mvm_vif {int /*<<< orphan*/  dbgfs_slink; int /*<<< orphan*/  dbgfs_dir; } ;
struct iwl_mvm {int /*<<< orphan*/  debugfs_dir; TYPE_1__* fw; struct iwl_mvm_vif* bf_allowed_vif; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; struct dentry* debugfs_dir; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_6__ {scalar_t__ power_scheme; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 scalar_t__ IWL_MVM_TOF_IS_RESPONDER ; 
 scalar_t__ IWL_POWER_SCHEME_CAM ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TOF_SUPPORT ; 
 int /*<<< orphan*/  MVM_DEBUGFS_ADD_FILE_VIF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  bf_params ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 TYPE_3__ iwlmvm_mod_params ; 
 int /*<<< orphan*/  low_latency ; 
 int /*<<< orphan*/  mac_params ; 
 int /*<<< orphan*/  os_device_timediff ; 
 int /*<<< orphan*/  pm_params ; 
 int /*<<< orphan*/  quota_min ; 
 int /*<<< orphan*/  rx_phyinfo ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tof_enable ; 
 int /*<<< orphan*/  tof_range_abort ; 
 int /*<<< orphan*/  tof_range_req_ext ; 
 int /*<<< orphan*/  tof_range_request ; 
 int /*<<< orphan*/  tof_range_response ; 
 int /*<<< orphan*/  tof_responder_params ; 
 int /*<<< orphan*/  tx_pwr_lmt ; 
 int /*<<< orphan*/  uapsd_misbehaving ; 

void iwl_mvm_vif_dbgfs_register(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct dentry *dbgfs_dir = vif->debugfs_dir;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	char buf[100];

	/*
	 * Check if debugfs directory already exist before creating it.
	 * This may happen when, for example, resetting hw or suspend-resume
	 */
	if (!dbgfs_dir || mvmvif->dbgfs_dir)
		return;

	mvmvif->dbgfs_dir = debugfs_create_dir("iwlmvm", dbgfs_dir);

	if (!mvmvif->dbgfs_dir) {
		IWL_ERR(mvm, "Failed to create debugfs directory under %pd\n",
			dbgfs_dir);
		return;
	}

	if (iwlmvm_mod_params.power_scheme != IWL_POWER_SCHEME_CAM &&
	    ((vif->type == NL80211_IFTYPE_STATION && !vif->p2p) ||
	     (vif->type == NL80211_IFTYPE_STATION && vif->p2p)))
		MVM_DEBUGFS_ADD_FILE_VIF(pm_params, mvmvif->dbgfs_dir, 0600);

	MVM_DEBUGFS_ADD_FILE_VIF(tx_pwr_lmt, mvmvif->dbgfs_dir, 0400);
	MVM_DEBUGFS_ADD_FILE_VIF(mac_params, mvmvif->dbgfs_dir, 0400);
	MVM_DEBUGFS_ADD_FILE_VIF(low_latency, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(uapsd_misbehaving, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(rx_phyinfo, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(quota_min, mvmvif->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_FILE_VIF(os_device_timediff, mvmvif->dbgfs_dir, 0400);

	if (vif->type == NL80211_IFTYPE_STATION && !vif->p2p &&
	    mvmvif == mvm->bf_allowed_vif)
		MVM_DEBUGFS_ADD_FILE_VIF(bf_params, mvmvif->dbgfs_dir, 0600);

	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_TOF_SUPPORT) &&
	    !vif->p2p && (vif->type != NL80211_IFTYPE_P2P_DEVICE)) {
		if (IWL_MVM_TOF_IS_RESPONDER && vif->type == NL80211_IFTYPE_AP)
			MVM_DEBUGFS_ADD_FILE_VIF(tof_responder_params,
						 mvmvif->dbgfs_dir, 0600);

		MVM_DEBUGFS_ADD_FILE_VIF(tof_range_request, mvmvif->dbgfs_dir,
					 0600);
		MVM_DEBUGFS_ADD_FILE_VIF(tof_range_req_ext, mvmvif->dbgfs_dir,
					 0600);
		MVM_DEBUGFS_ADD_FILE_VIF(tof_enable, mvmvif->dbgfs_dir,
					 0600);
		MVM_DEBUGFS_ADD_FILE_VIF(tof_range_abort, mvmvif->dbgfs_dir,
					 0600);
		MVM_DEBUGFS_ADD_FILE_VIF(tof_range_response, mvmvif->dbgfs_dir,
					 0400);
	}

	/*
	 * Create symlink for convenience pointing to interface specific
	 * debugfs entries for the driver. For example, under
	 * /sys/kernel/debug/iwlwifi/0000\:02\:00.0/iwlmvm/
	 * find
	 * netdev:wlan0 -> ../../../ieee80211/phy0/netdev:wlan0/iwlmvm/
	 */
	snprintf(buf, 100, "../../../%pd3/%pd",
		 dbgfs_dir,
		 mvmvif->dbgfs_dir);

	mvmvif->dbgfs_slink = debugfs_create_symlink(dbgfs_dir->d_name.name,
						     mvm->debugfs_dir, buf);
	if (!mvmvif->dbgfs_slink)
		IWL_ERR(mvm, "Can't create debugfs symbolic link under %pd\n",
			dbgfs_dir);
	return;
err:
	IWL_ERR(mvm, "Can't create debugfs entity\n");
}
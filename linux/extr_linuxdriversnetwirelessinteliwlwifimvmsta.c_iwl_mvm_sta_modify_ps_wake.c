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
struct iwl_mvm_sta {int /*<<< orphan*/  mac_id_n_color; int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm_add_sta_cmd {int /*<<< orphan*/  mac_id_n_color; int /*<<< orphan*/  station_flags_msk; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  add_modify; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STA ; 
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  STA_FLG_PS ; 
 int /*<<< orphan*/  STA_MODE_MODIFY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_add_sta_cmd_size (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_add_sta_cmd*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 

void iwl_mvm_sta_modify_ps_wake(struct iwl_mvm *mvm,
				struct ieee80211_sta *sta)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	struct iwl_mvm_add_sta_cmd cmd = {
		.add_modify = STA_MODE_MODIFY,
		.sta_id = mvmsta->sta_id,
		.station_flags_msk = cpu_to_le32(STA_FLG_PS),
		.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color),
	};
	int ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA, CMD_ASYNC,
				   iwl_mvm_add_sta_cmd_size(mvm), &cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to send ADD_STA command (%d)\n", ret);
}
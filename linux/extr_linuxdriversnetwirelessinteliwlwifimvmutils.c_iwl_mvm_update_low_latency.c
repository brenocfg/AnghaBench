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
struct iwl_mvm_vif {int /*<<< orphan*/  id; } ;
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  mutex; } ;
struct iwl_mac_low_latency_cmd {int low_latency_rx; int low_latency_tx; int /*<<< orphan*/  mac_id; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum iwl_mvm_low_latency_cause { ____Placeholder_iwl_mvm_low_latency_cause } iwl_mvm_low_latency_cause ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA ; 
 int /*<<< orphan*/  LOW_LATENCY_CMD ; 
 int /*<<< orphan*/  MAC_CONF_GROUP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_bt_coex_vif_change (struct iwl_mvm*) ; 
 int iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mac_low_latency_cmd*) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,int,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int iwl_mvm_vif_low_latency (struct iwl_mvm_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_vif_set_low_latency (struct iwl_mvm_vif*,int,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_update_low_latency(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			       bool low_latency,
			       enum iwl_mvm_low_latency_cause cause)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int res;
	bool prev;

	lockdep_assert_held(&mvm->mutex);

	prev = iwl_mvm_vif_low_latency(mvmvif);
	iwl_mvm_vif_set_low_latency(mvmvif, low_latency, cause);

	low_latency = iwl_mvm_vif_low_latency(mvmvif);

	if (low_latency == prev)
		return 0;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA)) {
		struct iwl_mac_low_latency_cmd cmd = {
			.mac_id = cpu_to_le32(mvmvif->id)
		};

		if (low_latency) {
			/* currently we don't care about the direction */
			cmd.low_latency_rx = 1;
			cmd.low_latency_tx = 1;
		}
		res = iwl_mvm_send_cmd_pdu(mvm,
					   iwl_cmd_id(LOW_LATENCY_CMD,
						      MAC_CONF_GROUP, 0),
					   0, sizeof(cmd), &cmd);
		if (res)
			IWL_ERR(mvm, "Failed to send low latency command\n");
	}

	res = iwl_mvm_update_quotas(mvm, false, NULL);
	if (res)
		return res;

	iwl_mvm_bt_coex_vif_change(mvm);

	return iwl_mvm_power_update_mac(mvm);
}
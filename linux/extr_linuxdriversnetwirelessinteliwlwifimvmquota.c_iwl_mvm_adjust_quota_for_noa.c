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
struct iwl_time_quota_cmd {int dummy; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void iwl_mvm_adjust_quota_for_noa(struct iwl_mvm *mvm,
					 struct iwl_time_quota_cmd *cmd)
{
#ifdef CONFIG_NL80211_TESTMODE
	struct iwl_mvm_vif *mvmvif;
	int i, phy_id = -1, beacon_int = 0;

	if (!mvm->noa_duration || !mvm->noa_vif)
		return;

	mvmvif = iwl_mvm_vif_from_mac80211(mvm->noa_vif);
	if (!mvmvif->ap_ibss_active)
		return;

	phy_id = mvmvif->phy_ctxt->id;
	beacon_int = mvm->noa_vif->bss_conf.beacon_int;

	for (i = 0; i < MAX_BINDINGS; i++) {
		struct iwl_time_quota_data *data =
					iwl_mvm_quota_cmd_get_quota(mvm, cmd,
								    i);
		u32 id_n_c = le32_to_cpu(data->id_and_color);
		u32 id = (id_n_c & FW_CTXT_ID_MSK) >> FW_CTXT_ID_POS;
		u32 quota = le32_to_cpu(data->quota);

		if (id != phy_id)
			continue;

		quota *= (beacon_int - mvm->noa_duration);
		quota /= beacon_int;

		IWL_DEBUG_QUOTA(mvm, "quota: adjust for NoA from %d to %d\n",
				le32_to_cpu(data->quota), quota);

		data->quota = cpu_to_le32(quota);
	}
#endif
}
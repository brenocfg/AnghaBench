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
struct iwl_mvm_tcm_iter_data {int any_sent; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_1__* fw; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_UMAC_SCAN ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_tcm_iter_data*) ; 
 int /*<<< orphan*/  iwl_mvm_config_scan (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_tcm_iter ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_tcm_results(struct iwl_mvm *mvm)
{
	struct iwl_mvm_tcm_iter_data data = {
		.mvm = mvm,
		.any_sent = false,
	};

	mutex_lock(&mvm->mutex);

	ieee80211_iterate_active_interfaces(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_tcm_iter, &data);

	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN))
		iwl_mvm_config_scan(mvm);

	mutex_unlock(&mvm->mutex);
}
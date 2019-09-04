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
struct TYPE_2__ {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {TYPE_1__ snif_sta; int /*<<< orphan*/  snif_queue; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_TX_FIFO_BE ; 
 int iwl_mvm_add_int_sta_common (struct iwl_mvm*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_enable_aux_snif_queue (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_add_snif_sta(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	lockdep_assert_held(&mvm->mutex);

	/* Map snif queue to fifo - must happen before adding snif station */
	if (!iwl_mvm_has_new_tx_api(mvm))
		iwl_mvm_enable_aux_snif_queue(mvm, &mvm->snif_queue,
					      mvm->snif_sta.sta_id,
					      IWL_MVM_TX_FIFO_BE);

	ret = iwl_mvm_add_int_sta_common(mvm, &mvm->snif_sta, vif->addr,
					 mvmvif->id, 0);
	if (ret)
		return ret;

	/*
	 * For 22000 firmware and on we cannot add queue to a station unknown
	 * to firmware so enable queue here - after the station was added
	 */
	if (iwl_mvm_has_new_tx_api(mvm))
		iwl_mvm_enable_aux_snif_queue(mvm, &mvm->snif_queue,
					      mvm->snif_sta.sta_id,
					      IWL_MVM_TX_FIFO_BE);

	return 0;
}
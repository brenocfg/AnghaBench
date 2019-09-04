#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {TYPE_1__ aux_sta; int /*<<< orphan*/  aux_queue; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_MVM_TX_FIFO_MCAST ; 
 int /*<<< orphan*/  IWL_STA_AUX_ACTIVITY ; 
 int /*<<< orphan*/  MAC_INDEX_AUX ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int iwl_mvm_add_int_sta_common (struct iwl_mvm*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_allocate_int_sta (struct iwl_mvm*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_int_sta (struct iwl_mvm*,TYPE_1__*) ; 
 int /*<<< orphan*/  iwl_mvm_enable_aux_snif_queue (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_add_aux_sta(struct iwl_mvm *mvm)
{
	int ret;

	lockdep_assert_held(&mvm->mutex);

	/* Allocate aux station and assign to it the aux queue */
	ret = iwl_mvm_allocate_int_sta(mvm, &mvm->aux_sta, BIT(mvm->aux_queue),
				       NL80211_IFTYPE_UNSPECIFIED,
				       IWL_STA_AUX_ACTIVITY);
	if (ret)
		return ret;

	/* Map Aux queue to fifo - needs to happen before adding Aux station */
	if (!iwl_mvm_has_new_tx_api(mvm))
		iwl_mvm_enable_aux_snif_queue(mvm, &mvm->aux_queue,
					      mvm->aux_sta.sta_id,
					      IWL_MVM_TX_FIFO_MCAST);

	ret = iwl_mvm_add_int_sta_common(mvm, &mvm->aux_sta, NULL,
					 MAC_INDEX_AUX, 0);
	if (ret) {
		iwl_mvm_dealloc_int_sta(mvm, &mvm->aux_sta);
		return ret;
	}

	/*
	 * For 22000 firmware and on we cannot add queue to a station unknown
	 * to firmware so enable queue here - after the station was added
	 */
	if (iwl_mvm_has_new_tx_api(mvm))
		iwl_mvm_enable_aux_snif_queue(mvm, &mvm->aux_queue,
					      mvm->aux_sta.sta_id,
					      IWL_MVM_TX_FIFO_MCAST);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm {TYPE_2__* cfg; } ;
struct ieee80211_sta_vht_cap {int cap; scalar_t__ vht_supported; } ;
struct ieee80211_sta_ht_cap {int cap; } ;
struct ieee80211_sta {struct ieee80211_sta_vht_cap vht_cap; struct ieee80211_sta_ht_cap ht_cap; } ;
struct TYPE_4__ {TYPE_1__* ht_params; } ;
struct TYPE_3__ {scalar_t__ ldpc; scalar_t__ stbc; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_VHT_CAP_RXLDPC ; 
 int IEEE80211_VHT_CAP_RXSTBC_MASK ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CFG_FLAGS_STBC_MSK ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 rs_fw_set_config_flags(struct iwl_mvm *mvm,
				  struct ieee80211_sta *sta)
{
	struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	bool vht_ena = vht_cap && vht_cap->vht_supported;
	u16 flags = 0;

	if (mvm->cfg->ht_params->stbc &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1) &&
	    ((ht_cap && (ht_cap->cap & IEEE80211_HT_CAP_RX_STBC)) ||
	     (vht_ena && (vht_cap->cap & IEEE80211_VHT_CAP_RXSTBC_MASK))))
		flags |= IWL_TLC_MNG_CFG_FLAGS_STBC_MSK;

	if (mvm->cfg->ht_params->ldpc &&
	    ((ht_cap && (ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING)) ||
	     (vht_ena && (vht_cap->cap & IEEE80211_VHT_CAP_RXLDPC))))
		flags |= IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK;

	return flags;
}
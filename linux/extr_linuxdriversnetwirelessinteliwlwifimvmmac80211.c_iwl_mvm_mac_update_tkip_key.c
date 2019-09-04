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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {scalar_t__ hw_key_idx; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ STA_KEY_IDX_INVALID ; 
 int /*<<< orphan*/  iwl_mvm_update_tkip_key (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_key_conf*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_update_tkip_key(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif,
					struct ieee80211_key_conf *keyconf,
					struct ieee80211_sta *sta,
					u32 iv32, u16 *phase1key)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	if (keyconf->hw_key_idx == STA_KEY_IDX_INVALID)
		return;

	iwl_mvm_update_tkip_key(mvm, vif, keyconf, sta, iv32, phase1key);
}
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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_chanctx_conf {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  __iwl_mvm_unassign_vif_chanctx (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_chanctx_conf*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_unassign_vif_chanctx(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif,
					 struct ieee80211_chanctx_conf *ctx)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);
	__iwl_mvm_unassign_vif_chanctx(mvm, vif, ctx, false);
	mutex_unlock(&mvm->mutex);
}
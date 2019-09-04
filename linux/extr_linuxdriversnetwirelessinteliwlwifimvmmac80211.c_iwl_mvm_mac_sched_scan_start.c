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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  idle; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_scan_ies {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct cfg80211_sched_scan_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_SCAN_SCHED ; 
 int iwl_mvm_sched_scan_start (struct iwl_mvm*,struct ieee80211_vif*,struct cfg80211_sched_scan_request*,struct ieee80211_scan_ies*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_mac_sched_scan_start(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif,
					struct cfg80211_sched_scan_request *req,
					struct ieee80211_scan_ies *ies)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	int ret;

	mutex_lock(&mvm->mutex);

	if (!vif->bss_conf.idle) {
		ret = -EBUSY;
		goto out;
	}

	ret = iwl_mvm_sched_scan_start(mvm, vif, req, ies, IWL_MVM_SCAN_SCHED);

out:
	mutex_unlock(&mvm->mutex);
	return ret;
}
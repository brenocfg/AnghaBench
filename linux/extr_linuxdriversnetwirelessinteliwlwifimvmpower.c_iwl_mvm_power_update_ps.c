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
struct iwl_power_vifs {scalar_t__ bss_vif; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_power_vifs*) ; 
 int /*<<< orphan*/  iwl_mvm_power_get_vifs_iterator ; 
 int iwl_mvm_power_set_ba (struct iwl_mvm*,scalar_t__) ; 
 int iwl_mvm_power_set_ps (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_power_update_ps(struct iwl_mvm *mvm)
{
	struct iwl_power_vifs vifs = {
		.mvm = mvm,
	};
	int ret;

	lockdep_assert_held(&mvm->mutex);

	/* get vifs info */
	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_power_get_vifs_iterator, &vifs);

	ret = iwl_mvm_power_set_ps(mvm);
	if (ret)
		return ret;

	if (vifs.bss_vif)
		return iwl_mvm_power_set_ba(mvm, vifs.bss_vif);

	return 0;
}
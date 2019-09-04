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
struct iwl_mvm {int ps_disabled; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {scalar_t__ power_scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 scalar_t__ IWL_POWER_SCHEME_CAM ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iwl_mvm_power_ps_disabled_iterator ; 
 int iwl_mvm_power_update_device (struct iwl_mvm*) ; 
 TYPE_1__ iwlmvm_mod_params ; 

__attribute__((used)) static int iwl_mvm_power_set_ps(struct iwl_mvm *mvm)
{
	bool disable_ps;
	int ret;

	/* disable PS if CAM */
	disable_ps = (iwlmvm_mod_params.power_scheme == IWL_POWER_SCHEME_CAM);
	/* ...or if any of the vifs require PS to be off */
	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_power_ps_disabled_iterator,
					&disable_ps);

	/* update device power state if it has changed */
	if (mvm->ps_disabled != disable_ps) {
		bool old_ps_disabled = mvm->ps_disabled;

		mvm->ps_disabled = disable_ps;
		ret = iwl_mvm_power_update_device(mvm);
		if (ret) {
			mvm->ps_disabled = old_ps_disabled;
			return ret;
		}
	}

	return 0;
}
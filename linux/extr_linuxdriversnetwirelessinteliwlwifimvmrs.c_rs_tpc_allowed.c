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
struct rs_rate {int index; int /*<<< orphan*/  type; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ps; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_4__ {scalar_t__ power_scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,int,...) ; 
 scalar_t__ IWL_POWER_SCHEME_CAM ; 
 int IWL_RATE_54M_INDEX ; 
 int IWL_RATE_MCS_7_INDEX ; 
 int IWL_RATE_MCS_8_INDEX ; 
 int IWL_RATE_MCS_9_INDEX ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ is_ht (struct rs_rate*) ; 
 scalar_t__ is_legacy (struct rs_rate*) ; 
 scalar_t__ is_vht (struct rs_rate*) ; 
 int /*<<< orphan*/  iwl_mvm_bt_coex_is_tpc_allowed (struct iwl_mvm*,int) ; 
 TYPE_2__ iwlmvm_mod_params ; 

__attribute__((used)) static bool rs_tpc_allowed(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			   struct rs_rate *rate, enum nl80211_band band)
{
	int index = rate->index;
	bool cam = (iwlmvm_mod_params.power_scheme == IWL_POWER_SCHEME_CAM);
	bool sta_ps_disabled = (vif->type == NL80211_IFTYPE_STATION &&
				!vif->bss_conf.ps);

	IWL_DEBUG_RATE(mvm, "cam: %d sta_ps_disabled %d\n",
		       cam, sta_ps_disabled);
	/*
	 * allow tpc only if power management is enabled, or bt coex
	 * activity grade allows it and we are on 2.4Ghz.
	 */
	if ((cam || sta_ps_disabled) &&
	    !iwl_mvm_bt_coex_is_tpc_allowed(mvm, band))
		return false;

	IWL_DEBUG_RATE(mvm, "check rate, table type: %d\n", rate->type);
	if (is_legacy(rate))
		return index == IWL_RATE_54M_INDEX;
	if (is_ht(rate))
		return index == IWL_RATE_MCS_7_INDEX;
	if (is_vht(rate))
		return index == IWL_RATE_MCS_7_INDEX ||
		       index == IWL_RATE_MCS_8_INDEX ||
		       index == IWL_RATE_MCS_9_INDEX;

	WARN_ON_ONCE(1);
	return false;
}
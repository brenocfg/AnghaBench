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
struct iwl_mvm {TYPE_1__* hw; } ;
struct ieee80211_regdomain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct ieee80211_regdomain*) ; 
 struct ieee80211_regdomain* iwl_mvm_get_current_regdomain (struct iwl_mvm*,int*) ; 
 int /*<<< orphan*/  iwl_mvm_is_lar_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_regdomain*) ; 
 int /*<<< orphan*/  regulatory_set_wiphy_regd (int /*<<< orphan*/ ,struct ieee80211_regdomain*) ; 

void iwl_mvm_update_changed_regdom(struct iwl_mvm *mvm)
{
	bool changed;
	struct ieee80211_regdomain *regd;

	if (!iwl_mvm_is_lar_supported(mvm))
		return;

	regd = iwl_mvm_get_current_regdomain(mvm, &changed);
	if (!IS_ERR_OR_NULL(regd)) {
		/* only update the regulatory core if changed */
		if (changed)
			regulatory_set_wiphy_regd(mvm->hw->wiphy, regd);

		kfree(regd);
	}
}
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
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 scalar_t__ iwl_mvm_has_tlc_offload (struct iwl_mvm*) ; 
 int /*<<< orphan*/  rs_drv_rate_init (struct iwl_mvm*,struct ieee80211_sta*,int,int) ; 
 int /*<<< orphan*/  rs_fw_rate_init (struct iwl_mvm*,struct ieee80211_sta*,int) ; 

void iwl_mvm_rs_rate_init(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			  enum nl80211_band band, bool update)
{
	if (iwl_mvm_has_tlc_offload(mvm))
		rs_fw_rate_init(mvm, sta, band);
	else
		rs_drv_rate_init(mvm, sta, band, update);
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_HIGH_PRIO ; 
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  iwl_mvm_update_d0i3_power_mode (struct iwl_mvm*,struct ieee80211_vif*,int,int) ; 

__attribute__((used)) static void iwl_mvm_exit_d0i3_iterator(void *_data, u8 *mac,
				       struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = _data;
	u32 flags = CMD_ASYNC | CMD_HIGH_PRIO;

	IWL_DEBUG_RPM(mvm, "exiting D0i3 - vif %pM\n", vif->addr);
	if (vif->type != NL80211_IFTYPE_STATION ||
	    !vif->bss_conf.assoc)
		return;

	iwl_mvm_update_d0i3_power_mode(mvm, vif, false, flags);
}
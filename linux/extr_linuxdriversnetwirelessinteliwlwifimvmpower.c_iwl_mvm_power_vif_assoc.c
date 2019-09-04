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
struct iwl_mvm_vif {int /*<<< orphan*/  uapsd_misbehaving_bssid; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_mvm_power_vif_assoc(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (memcmp(vif->bss_conf.bssid, mvmvif->uapsd_misbehaving_bssid,
		   ETH_ALEN))
		eth_zero_addr(mvmvif->uapsd_misbehaving_bssid);
}
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
typedef  scalar_t__ u8 ;
struct iwl_mvm_vif {scalar_t__ ap_sta_id; int /*<<< orphan*/  uapsd_misbehaving_bssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_power_uapsd_misbehav_ap_iterator(void *_data, u8 *mac,
						     struct ieee80211_vif *vif)
{
	u8 *ap_sta_id = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	/* The ap_sta_id is not expected to change during current association
	 * so no explicit protection is needed
	 */
	if (mvmvif->ap_sta_id == *ap_sta_id)
		memcpy(mvmvif->uapsd_misbehaving_bssid, vif->bss_conf.bssid,
		       ETH_ALEN);
}
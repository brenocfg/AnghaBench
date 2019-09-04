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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_vif {scalar_t__ ap_ibss_active; } ;
struct iwl_mvm_go_iterator_data {int go_active; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_go_iterator(void *_data, u8 *mac, struct ieee80211_vif *vif)
{
	struct iwl_mvm_go_iterator_data *data = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (vif->type == NL80211_IFTYPE_AP && vif->p2p &&
	    mvmvif->ap_ibss_active)
		data->go_active = true;
}
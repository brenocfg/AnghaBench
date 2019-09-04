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
struct iwl_bss_iter_data {int error; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 

__attribute__((used)) static void iwl_mvm_bss_iface_iterator(void *_data, u8 *mac,
				       struct ieee80211_vif *vif)
{
	struct iwl_bss_iter_data *data = _data;

	if (vif->type != NL80211_IFTYPE_STATION || vif->p2p)
		return;

	if (data->vif) {
		data->error = true;
		return;
	}

	data->vif = vif;
}
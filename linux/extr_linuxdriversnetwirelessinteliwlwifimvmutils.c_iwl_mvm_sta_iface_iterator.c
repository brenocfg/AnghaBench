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
struct iwl_sta_iter_data {int assoc; } ;
struct TYPE_2__ {scalar_t__ assoc; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 

__attribute__((used)) static void iwl_mvm_sta_iface_iterator(void *_data, u8 *mac,
				       struct ieee80211_vif *vif)
{
	struct iwl_sta_iter_data *data = _data;

	if (vif->type != NL80211_IFTYPE_STATION)
		return;

	if (vif->bss_conf.assoc)
		data->assoc = true;
}
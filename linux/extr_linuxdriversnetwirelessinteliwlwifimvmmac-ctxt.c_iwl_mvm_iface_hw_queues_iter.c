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
struct iwl_mvm_hw_queues_iface_iterator_data {int /*<<< orphan*/  used_hw_queues; struct ieee80211_vif* exclude_vif; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_mac_get_queues_mask (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_iface_hw_queues_iter(void *_data, u8 *mac,
					 struct ieee80211_vif *vif)
{
	struct iwl_mvm_hw_queues_iface_iterator_data *data = _data;

	/* exclude the given vif */
	if (vif == data->exclude_vif)
		return;

	data->used_hw_queues |= iwl_mvm_mac_get_queues_mask(vif);
}
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
struct iwl_mvm_vif {scalar_t__ phy_ctxt; int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm_iface_iterator_data {scalar_t__ phyctxt; size_t idx; int /*<<< orphan*/ * colors; int /*<<< orphan*/ * ids; struct ieee80211_vif* ignore_vif; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 size_t MAX_MACS_IN_BINDING ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_iface_iterator(void *_data, u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct iwl_mvm_iface_iterator_data *data = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (vif == data->ignore_vif)
		return;

	if (mvmvif->phy_ctxt != data->phyctxt)
		return;

	if (WARN_ON_ONCE(data->idx >= MAX_MACS_IN_BINDING))
		return;

	data->ids[data->idx] = mvmvif->id;
	data->colors[data->idx] = mvmvif->color;
	data->idx++;
}
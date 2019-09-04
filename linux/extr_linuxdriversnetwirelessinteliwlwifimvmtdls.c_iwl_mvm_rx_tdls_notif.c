#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct iwl_tdls_channel_switch_notif {int /*<<< orphan*/  status; int /*<<< orphan*/  sta_id; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_sta {struct ieee80211_vif* vif; } ;
struct TYPE_4__ {int /*<<< orphan*/  dwork; } ;
struct iwl_mvm {TYPE_2__ tdls_cs; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct TYPE_3__ {int dtim_period; int beacon_int; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_sta {int /*<<< orphan*/  tdls; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 size_t IWL_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  IWL_MVM_TDLS_SW_ACTIVE ; 
 int /*<<< orphan*/  IWL_MVM_TDLS_SW_IDLE ; 
 unsigned int TU_TO_MS (int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_tdls_update_cs_state (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  system_wq ; 

void iwl_mvm_rx_tdls_notif(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_tdls_channel_switch_notif *notif = (void *)pkt->data;
	struct ieee80211_sta *sta;
	unsigned int delay;
	struct iwl_mvm_sta *mvmsta;
	struct ieee80211_vif *vif;
	u32 sta_id = le32_to_cpu(notif->sta_id);

	lockdep_assert_held(&mvm->mutex);

	/* can fail sometimes */
	if (!le32_to_cpu(notif->status)) {
		iwl_mvm_tdls_update_cs_state(mvm, IWL_MVM_TDLS_SW_IDLE);
		return;
	}

	if (WARN_ON(sta_id >= IWL_MVM_STATION_COUNT))
		return;

	sta = rcu_dereference_protected(mvm->fw_id_to_mac_id[sta_id],
					lockdep_is_held(&mvm->mutex));
	/* the station may not be here, but if it is, it must be a TDLS peer */
	if (IS_ERR_OR_NULL(sta) || WARN_ON(!sta->tdls))
		return;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	vif = mvmsta->vif;

	/*
	 * Update state and possibly switch again after this is over (DTIM).
	 * Also convert TU to msec.
	 */
	delay = TU_TO_MS(vif->bss_conf.dtim_period * vif->bss_conf.beacon_int);
	mod_delayed_work(system_wq, &mvm->tdls_cs.dwork,
			 msecs_to_jiffies(delay));

	iwl_mvm_tdls_update_cs_state(mvm, IWL_MVM_TDLS_SW_ACTIVE);
}
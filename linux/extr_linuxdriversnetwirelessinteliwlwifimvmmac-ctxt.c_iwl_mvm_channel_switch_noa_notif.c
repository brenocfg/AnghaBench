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
typedef  scalar_t__ u32 ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm {int /*<<< orphan*/  csa_vif; int /*<<< orphan*/  cs_tx_unblock_dwork; } ;
struct iwl_channel_switch_noa_notif {int /*<<< orphan*/  id_and_color; } ;
struct TYPE_2__ {int beacon_int; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; int /*<<< orphan*/  csa_active; } ;

/* Variables and functions */
 scalar_t__ FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*) ; 
 int IWL_MVM_CS_UNBLOCK_TX_TIMEOUT ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ WARN (int,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_csa_finish (struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct ieee80211_vif* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iwl_mvm_channel_switch_noa_notif(struct iwl_mvm *mvm,
				      struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_channel_switch_noa_notif *notif = (void *)pkt->data;
	struct ieee80211_vif *csa_vif;
	struct iwl_mvm_vif *mvmvif;
	int len = iwl_rx_packet_payload_len(pkt);
	u32 id_n_color;

	if (WARN_ON_ONCE(len < sizeof(*notif)))
		return;

	rcu_read_lock();

	csa_vif = rcu_dereference(mvm->csa_vif);
	if (WARN_ON(!csa_vif || !csa_vif->csa_active))
		goto out_unlock;

	id_n_color = le32_to_cpu(notif->id_and_color);

	mvmvif = iwl_mvm_vif_from_mac80211(csa_vif);
	if (WARN(FW_CMD_ID_AND_COLOR(mvmvif->id, mvmvif->color) != id_n_color,
		 "channel switch noa notification on unexpected vif (csa_vif=%d, notif=%d)",
		 FW_CMD_ID_AND_COLOR(mvmvif->id, mvmvif->color), id_n_color))
		goto out_unlock;

	IWL_DEBUG_INFO(mvm, "Channel Switch Started Notification\n");

	schedule_delayed_work(&mvm->cs_tx_unblock_dwork,
			      msecs_to_jiffies(IWL_MVM_CS_UNBLOCK_TX_TIMEOUT *
					       csa_vif->bss_conf.beacon_int));

	ieee80211_csa_finish(csa_vif);

	rcu_read_unlock();

	RCU_INIT_POINTER(mvm->csa_vif, NULL);

	return;

out_unlock:
	rcu_read_unlock();
}
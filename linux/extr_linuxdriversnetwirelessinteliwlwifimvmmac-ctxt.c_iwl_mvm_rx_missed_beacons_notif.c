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
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct iwl_missed_beacons_notif {int /*<<< orphan*/  num_expected_beacons; int /*<<< orphan*/  num_recvd_beacons; int /*<<< orphan*/  consec_missed_beacons_since_last_rx; int /*<<< orphan*/  consec_missed_beacons; int /*<<< orphan*/  mac_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_missed_beacons_notif*) ; 
 int /*<<< orphan*/  iwl_mvm_beacon_loss_iterator ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_missed_beacons_notif(struct iwl_mvm *mvm,
				     struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_missed_beacons_notif *mb = (void *)pkt->data;

	IWL_DEBUG_INFO(mvm,
		       "missed bcn mac_id=%u, consecutive=%u (%u, %u, %u)\n",
		       le32_to_cpu(mb->mac_id),
		       le32_to_cpu(mb->consec_missed_beacons),
		       le32_to_cpu(mb->consec_missed_beacons_since_last_rx),
		       le32_to_cpu(mb->num_recvd_beacons),
		       le32_to_cpu(mb->num_expected_beacons));

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_beacon_loss_iterator,
						   mb);
}
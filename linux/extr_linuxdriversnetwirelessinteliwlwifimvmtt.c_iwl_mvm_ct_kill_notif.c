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
struct iwl_mvm {int dummy; } ;
struct ct_kill_notif {int /*<<< orphan*/  temperature; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_enter_ctkill (struct iwl_mvm*) ; 
 int iwl_rx_packet_payload_len (struct iwl_rx_packet*) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_ct_kill_notif(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct ct_kill_notif *notif;
	int len = iwl_rx_packet_payload_len(pkt);

	if (WARN_ON_ONCE(len != sizeof(*notif))) {
		IWL_ERR(mvm, "Invalid CT_KILL_NOTIFICATION\n");
		return;
	}

	notif = (struct ct_kill_notif *)pkt->data;
	IWL_DEBUG_TEMP(mvm, "CT Kill notification temperature = %d\n",
		       notif->temperature);

	iwl_mvm_enter_ctkill(mvm);
}
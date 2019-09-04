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
struct iwl_mvm_tx_resp {int frame_count; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_rx_tx_cmd_agg (struct iwl_mvm*,struct iwl_rx_packet*) ; 
 int /*<<< orphan*/  iwl_mvm_rx_tx_cmd_single (struct iwl_mvm*,struct iwl_rx_packet*) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_tx_cmd(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_mvm_tx_resp *tx_resp = (void *)pkt->data;

	if (tx_resp->frame_count == 1)
		iwl_mvm_rx_tx_cmd_single(mvm, pkt);
	else
		iwl_mvm_rx_tx_cmd_agg(mvm, pkt);
}
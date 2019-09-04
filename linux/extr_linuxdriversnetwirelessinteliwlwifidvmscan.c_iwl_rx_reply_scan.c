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
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void iwl_rx_reply_scan(struct iwl_priv *priv,
			      struct iwl_rx_cmd_buffer *rxb)
{
#ifdef CONFIG_IWLWIFI_DEBUG
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_scanreq_notification *notif = (void *)pkt->data;

	IWL_DEBUG_SCAN(priv, "Scan request status = 0x%x\n", notif->status);
#endif
}
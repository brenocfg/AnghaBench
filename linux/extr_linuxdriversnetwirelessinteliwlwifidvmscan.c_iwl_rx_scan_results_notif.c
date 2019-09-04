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

__attribute__((used)) static void iwl_rx_scan_results_notif(struct iwl_priv *priv,
				      struct iwl_rx_cmd_buffer *rxb)
{
#ifdef CONFIG_IWLWIFI_DEBUG
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_scanresults_notification *notif = (void *)pkt->data;

	IWL_DEBUG_SCAN(priv, "Scan ch.res: "
		       "%d [802.11%s] "
		       "probe status: %u:%u "
		       "(TSF: 0x%08X:%08X) - %d "
		       "elapsed=%lu usec\n",
		       notif->channel,
		       notif->band ? "bg" : "a",
		       notif->probe_status, notif->num_probe_not_sent,
		       le32_to_cpu(notif->tsf_high),
		       le32_to_cpu(notif->tsf_low),
		       le32_to_cpu(notif->statistics[0]),
		       le32_to_cpu(notif->tsf_low) - priv->scan_start_tsf);
#endif
}
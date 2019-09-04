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
struct iwl_scanstart_notification {int /*<<< orphan*/  beacon_timer; int /*<<< orphan*/  status; int /*<<< orphan*/  tsf_low; int /*<<< orphan*/  tsf_high; scalar_t__ band; int /*<<< orphan*/  channel; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  scan_start_tsf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static void iwl_rx_scan_start_notif(struct iwl_priv *priv,
				    struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_scanstart_notification *notif = (void *)pkt->data;

	priv->scan_start_tsf = le32_to_cpu(notif->tsf_low);
	IWL_DEBUG_SCAN(priv, "Scan start: "
		       "%d [802.11%s] "
		       "(TSF: 0x%08X:%08X) - %d (beacon timer %u)\n",
		       notif->channel,
		       notif->band ? "bg" : "a",
		       le32_to_cpu(notif->tsf_high),
		       le32_to_cpu(notif->tsf_low),
		       notif->status, notif->beacon_timer);
}
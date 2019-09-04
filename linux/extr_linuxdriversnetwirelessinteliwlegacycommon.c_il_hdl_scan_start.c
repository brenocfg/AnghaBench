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
struct il_scanstart_notification {int /*<<< orphan*/  beacon_timer; int /*<<< orphan*/  status; int /*<<< orphan*/  tsf_low; int /*<<< orphan*/  tsf_high; scalar_t__ band; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {scalar_t__ raw; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int /*<<< orphan*/  scan_start_tsf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

__attribute__((used)) static void
il_hdl_scan_start(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_scanstart_notification *notif =
	    (struct il_scanstart_notification *)pkt->u.raw;
	il->scan_start_tsf = le32_to_cpu(notif->tsf_low);
	D_SCAN("Scan start: " "%d [802.11%s] "
	       "(TSF: 0x%08X:%08X) - %d (beacon timer %u)\n", notif->channel,
	       notif->band ? "bg" : "a", le32_to_cpu(notif->tsf_high),
	       le32_to_cpu(notif->tsf_low), notif->status, notif->beacon_timer);
}
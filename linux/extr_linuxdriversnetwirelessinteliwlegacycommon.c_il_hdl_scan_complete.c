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
struct il_rx_buf {int dummy; } ;
struct il_priv {scalar_t__ scan_band; int /*<<< orphan*/  scan_completed; int /*<<< orphan*/  workqueue; scalar_t__ scan_start; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  tsf_high; int /*<<< orphan*/  tsf_low; int /*<<< orphan*/  scanned_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  S_SCAN_HW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* scan_notif ; 

__attribute__((used)) static void
il_hdl_scan_complete(struct il_priv *il, struct il_rx_buf *rxb)
{

#ifdef CONFIG_IWLEGACY_DEBUG
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_scancomplete_notification *scan_notif = (void *)pkt->u.raw;
#endif

	D_SCAN("Scan complete: %d channels (TSF 0x%08X:%08X) - %d\n",
	       scan_notif->scanned_channels, scan_notif->tsf_low,
	       scan_notif->tsf_high, scan_notif->status);

	/* The HW is no longer scanning */
	clear_bit(S_SCAN_HW, &il->status);

	D_SCAN("Scan on %sGHz took %dms\n",
	       (il->scan_band == NL80211_BAND_2GHZ) ? "2.4" : "5.2",
	       jiffies_to_msecs(jiffies - il->scan_start));

	queue_work(il->workqueue, &il->scan_completed);
}
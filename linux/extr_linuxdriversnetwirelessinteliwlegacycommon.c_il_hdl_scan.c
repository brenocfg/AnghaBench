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
struct il_rx_buf {int dummy; } ;
struct il_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
il_hdl_scan(struct il_priv *il, struct il_rx_buf *rxb)
{
#ifdef CONFIG_IWLEGACY_DEBUG
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_scanreq_notification *notif =
	    (struct il_scanreq_notification *)pkt->u.raw;

	D_SCAN("Scan request status = 0x%x\n", notif->status);
#endif
}
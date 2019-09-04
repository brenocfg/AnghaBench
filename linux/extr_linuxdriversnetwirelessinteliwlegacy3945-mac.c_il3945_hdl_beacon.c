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
struct il3945_beacon_notif {int /*<<< orphan*/  ibss_mgr_status; } ;
struct TYPE_2__ {struct il3945_beacon_notif beacon_status; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int /*<<< orphan*/  ibss_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

__attribute__((used)) static void
il3945_hdl_beacon(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il3945_beacon_notif *beacon = &(pkt->u.beacon_status);
#ifdef CONFIG_IWLEGACY_DEBUG
	u8 rate = beacon->beacon_notify_hdr.rate;

	D_RX("beacon status %x retries %d iss %d " "tsf %d %d rate %d\n",
	     le32_to_cpu(beacon->beacon_notify_hdr.status) & TX_STATUS_MSK,
	     beacon->beacon_notify_hdr.failure_frame,
	     le32_to_cpu(beacon->ibss_mgr_status),
	     le32_to_cpu(beacon->high_tsf), le32_to_cpu(beacon->low_tsf), rate);
#endif

	il->ibss_manager = le32_to_cpu(beacon->ibss_mgr_status);

}
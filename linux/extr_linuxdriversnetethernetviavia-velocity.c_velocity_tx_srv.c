#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct velocity_td_info {TYPE_3__* skb; } ;
struct TYPE_10__ {int numq; int* tail; scalar_t__* used; struct velocity_td_info** infos; struct tx_desc** rings; } ;
struct TYPE_7__ {int numtx; } ;
struct velocity_info {int mii_status; TYPE_5__* netdev; TYPE_4__ tx; TYPE_1__ options; } ;
struct TYPE_8__ {int len; int TSR; } ;
struct tx_desc {TYPE_2__ tdesc0; } ;
struct net_device_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_11__ {struct net_device_stats stats; } ;
struct TYPE_9__ {scalar_t__ len; } ;

/* Variables and functions */
 int AVAIL_TD (struct velocity_info*,int) ; 
 int OWNED_BY_NIC ; 
 int TSR0_ABT ; 
 int TSR0_CDH ; 
 int TSR0_CRS ; 
 int TSR0_OWC ; 
 int TSR0_TERR ; 
 int VELOCITY_LINK_FAIL ; 
 scalar_t__ netif_queue_stopped (TYPE_5__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  velocity_free_tx_buf (struct velocity_info*,struct velocity_td_info*,struct tx_desc*) ; 

__attribute__((used)) static int velocity_tx_srv(struct velocity_info *vptr)
{
	struct tx_desc *td;
	int qnum;
	int full = 0;
	int idx;
	int works = 0;
	struct velocity_td_info *tdinfo;
	struct net_device_stats *stats = &vptr->netdev->stats;

	for (qnum = 0; qnum < vptr->tx.numq; qnum++) {
		for (idx = vptr->tx.tail[qnum]; vptr->tx.used[qnum] > 0;
			idx = (idx + 1) % vptr->options.numtx) {

			/*
			 *	Get Tx Descriptor
			 */
			td = &(vptr->tx.rings[qnum][idx]);
			tdinfo = &(vptr->tx.infos[qnum][idx]);

			if (td->tdesc0.len & OWNED_BY_NIC)
				break;

			if ((works++ > 15))
				break;

			if (td->tdesc0.TSR & TSR0_TERR) {
				stats->tx_errors++;
				stats->tx_dropped++;
				if (td->tdesc0.TSR & TSR0_CDH)
					stats->tx_heartbeat_errors++;
				if (td->tdesc0.TSR & TSR0_CRS)
					stats->tx_carrier_errors++;
				if (td->tdesc0.TSR & TSR0_ABT)
					stats->tx_aborted_errors++;
				if (td->tdesc0.TSR & TSR0_OWC)
					stats->tx_window_errors++;
			} else {
				stats->tx_packets++;
				stats->tx_bytes += tdinfo->skb->len;
			}
			velocity_free_tx_buf(vptr, tdinfo, td);
			vptr->tx.used[qnum]--;
		}
		vptr->tx.tail[qnum] = idx;

		if (AVAIL_TD(vptr, qnum) < 1)
			full = 1;
	}
	/*
	 *	Look to see if we should kick the transmit network
	 *	layer for more work.
	 */
	if (netif_queue_stopped(vptr->netdev) && (full == 0) &&
	    (!(vptr->mii_status & VELOCITY_LINK_FAIL))) {
		netif_wake_queue(vptr->netdev);
	}
	return works;
}
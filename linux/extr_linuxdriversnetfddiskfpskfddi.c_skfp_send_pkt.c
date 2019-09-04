#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_5__ {TYPE_1__ gen; } ;
struct TYPE_6__ {scalar_t__ QueueSkb; int /*<<< orphan*/  SendSkbQueue; TYPE_2__ MacStat; } ;
struct s_smc {TYPE_3__ os; } ;
struct net_device {int dummy; } ;
typedef  TYPE_3__ skfddi_priv ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ FDDI_K_LLC_LEN ; 
 scalar_t__ FDDI_K_LLC_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct s_smc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  send_queued_packets (struct s_smc*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t skfp_send_pkt(struct sk_buff *skb,
				       struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;

	pr_debug("skfp_send_pkt\n");

	/*
	 * Verify that incoming transmit request is OK
	 *
	 * Note: The packet size check is consistent with other
	 *               Linux device drivers, although the correct packet
	 *               size should be verified before calling the
	 *               transmit routine.
	 */

	if (!(skb->len >= FDDI_K_LLC_ZLEN && skb->len <= FDDI_K_LLC_LEN)) {
		bp->MacStat.gen.tx_errors++;	/* bump error counter */
		// dequeue packets from xmt queue and send them
		netif_start_queue(dev);
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;	/* return "success" */
	}
	if (bp->QueueSkb == 0) {	// return with tbusy set: queue full

		netif_stop_queue(dev);
		return NETDEV_TX_BUSY;
	}
	bp->QueueSkb--;
	skb_queue_tail(&bp->SendSkbQueue, skb);
	send_queued_packets(netdev_priv(dev));
	if (bp->QueueSkb == 0) {
		netif_stop_queue(dev);
	}
	return NETDEV_TX_OK;

}
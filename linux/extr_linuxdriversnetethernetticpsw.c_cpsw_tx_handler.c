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
struct sk_buff {struct net_device* dev; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct cpsw_common {int /*<<< orphan*/  cpts; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpts_tx_timestamp (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpsw_tx_handler(void *token, int len, int status)
{
	struct netdev_queue	*txq;
	struct sk_buff		*skb = token;
	struct net_device	*ndev = skb->dev;
	struct cpsw_common	*cpsw = ndev_to_cpsw(ndev);

	/* Check whether the queue is stopped due to stalled tx dma, if the
	 * queue is stopped then start the queue as we have free desc for tx
	 */
	txq = netdev_get_tx_queue(ndev, skb_get_queue_mapping(skb));
	if (unlikely(netif_tx_queue_stopped(txq)))
		netif_tx_wake_queue(txq);

	cpts_tx_timestamp(cpsw->cpts, skb);
	ndev->stats.tx_packets++;
	ndev->stats.tx_bytes += len;
	dev_kfree_skb_any(skb);
}
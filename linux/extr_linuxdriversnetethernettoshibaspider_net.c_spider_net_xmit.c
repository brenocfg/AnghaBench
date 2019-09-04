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
struct spider_net_card {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spider_net_kick_tx_dma (struct spider_net_card*) ; 
 scalar_t__ spider_net_prepare_tx_descr (struct spider_net_card*,struct sk_buff*) ; 
 int /*<<< orphan*/  spider_net_release_tx_chain (struct spider_net_card*,int /*<<< orphan*/ ) ; 
 int spider_net_set_low_watermark (struct spider_net_card*) ; 

__attribute__((used)) static int
spider_net_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	int cnt;
	struct spider_net_card *card = netdev_priv(netdev);

	spider_net_release_tx_chain(card, 0);

	if (spider_net_prepare_tx_descr(card, skb) != 0) {
		netdev->stats.tx_dropped++;
		netif_stop_queue(netdev);
		return NETDEV_TX_BUSY;
	}

	cnt = spider_net_set_low_watermark(card);
	if (cnt < 5)
		spider_net_kick_tx_dma(card);
	return NETDEV_TX_OK;
}
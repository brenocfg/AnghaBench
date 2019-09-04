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
struct xlgmac_pkt_info {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  desc_count; } ;
struct xlgmac_ring {struct xlgmac_pkt_info pkt_info; } ;
struct xlgmac_hw_ops {int /*<<< orphan*/  (* dev_xmit ) (struct xlgmac_channel*) ;} ;
struct xlgmac_desc_ops {int /*<<< orphan*/  (* map_tx_skb ) (struct xlgmac_channel*,struct sk_buff*) ;} ;
struct xlgmac_pdata {struct xlgmac_channel* channel_head; struct xlgmac_hw_ops hw_ops; struct xlgmac_desc_ops desc_ops; } ;
struct xlgmac_channel {struct xlgmac_ring* tx_ring; int /*<<< orphan*/  queue_index; } ;
struct sk_buff {scalar_t__ len; int queue_mapping; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  XLGMAC_PR (char*,scalar_t__) ; 
 int /*<<< orphan*/  XLGMAC_TX_MAX_DESC_NR ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct xlgmac_pkt_info*,int /*<<< orphan*/ ,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct xlgmac_pdata*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_msg_pktdata (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_channel*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct xlgmac_channel*) ; 
 int /*<<< orphan*/  tx_err ; 
 int xlgmac_maybe_stop_tx_queue (struct xlgmac_channel*,struct xlgmac_ring*,int /*<<< orphan*/ ) ; 
 int xlgmac_prep_tso (struct sk_buff*,struct xlgmac_pkt_info*) ; 
 int /*<<< orphan*/  xlgmac_prep_tx_pkt (struct xlgmac_pdata*,struct xlgmac_ring*,struct sk_buff*,struct xlgmac_pkt_info*) ; 
 int /*<<< orphan*/  xlgmac_prep_vlan (struct sk_buff*,struct xlgmac_pkt_info*) ; 
 int /*<<< orphan*/  xlgmac_print_pkt (struct net_device*,struct sk_buff*,int) ; 

__attribute__((used)) static int xlgmac_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct xlgmac_pdata *pdata = netdev_priv(netdev);
	struct xlgmac_pkt_info *tx_pkt_info;
	struct xlgmac_desc_ops *desc_ops;
	struct xlgmac_channel *channel;
	struct xlgmac_hw_ops *hw_ops;
	struct netdev_queue *txq;
	struct xlgmac_ring *ring;
	int ret;

	desc_ops = &pdata->desc_ops;
	hw_ops = &pdata->hw_ops;

	XLGMAC_PR("skb->len = %d\n", skb->len);

	channel = pdata->channel_head + skb->queue_mapping;
	txq = netdev_get_tx_queue(netdev, channel->queue_index);
	ring = channel->tx_ring;
	tx_pkt_info = &ring->pkt_info;

	if (skb->len == 0) {
		netif_err(pdata, tx_err, netdev,
			  "empty skb received from stack\n");
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	/* Prepare preliminary packet info for TX */
	memset(tx_pkt_info, 0, sizeof(*tx_pkt_info));
	xlgmac_prep_tx_pkt(pdata, ring, skb, tx_pkt_info);

	/* Check that there are enough descriptors available */
	ret = xlgmac_maybe_stop_tx_queue(channel, ring,
					 tx_pkt_info->desc_count);
	if (ret)
		return ret;

	ret = xlgmac_prep_tso(skb, tx_pkt_info);
	if (ret) {
		netif_err(pdata, tx_err, netdev,
			  "error processing TSO packet\n");
		dev_kfree_skb_any(skb);
		return ret;
	}
	xlgmac_prep_vlan(skb, tx_pkt_info);

	if (!desc_ops->map_tx_skb(channel, skb)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	/* Report on the actual number of bytes (to be) sent */
	netdev_tx_sent_queue(txq, tx_pkt_info->tx_bytes);

	/* Configure required descriptor fields for transmission */
	hw_ops->dev_xmit(channel);

	if (netif_msg_pktdata(pdata))
		xlgmac_print_pkt(netdev, skb, true);

	/* Stop the queue in advance if there may not be enough descriptors */
	xlgmac_maybe_stop_tx_queue(channel, ring, XLGMAC_TX_MAX_DESC_NR);

	return NETDEV_TX_OK;
}
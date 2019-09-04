#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct TYPE_10__ {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_4__ stats; } ;
struct TYPE_9__ {TYPE_5__* dn; } ;
struct TYPE_8__ {scalar_t__ protocol; } ;
struct chnl_net {TYPE_3__ chnl; TYPE_2__ conn_req; int /*<<< orphan*/  flowenabled; TYPE_1__* netdev; } ;
struct cfpkt {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_11__ {int (* transmit ) (TYPE_5__*,struct cfpkt*) ;} ;
struct TYPE_7__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ CAIFPROTO_DATAGRAM_LOOP ; 
 int /*<<< orphan*/  CAIF_DIR_OUT ; 
 int NETDEV_TX_OK ; 
 struct cfpkt* cfpkt_fromnative (int /*<<< orphan*/ ,void*) ; 
 TYPE_6__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct chnl_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int stub1 (TYPE_5__*,struct cfpkt*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chnl_net_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct chnl_net *priv;
	struct cfpkt *pkt = NULL;
	int len;
	int result = -1;
	/* Get our private data. */
	priv = netdev_priv(dev);

	if (skb->len > priv->netdev->mtu) {
		pr_warn("Size of skb exceeded MTU\n");
		kfree_skb(skb);
		dev->stats.tx_errors++;
		return NETDEV_TX_OK;
	}

	if (!priv->flowenabled) {
		pr_debug("dropping packets flow off\n");
		kfree_skb(skb);
		dev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	if (priv->conn_req.protocol == CAIFPROTO_DATAGRAM_LOOP)
		swap(ip_hdr(skb)->saddr, ip_hdr(skb)->daddr);

	/* Store original SKB length. */
	len = skb->len;

	pkt = cfpkt_fromnative(CAIF_DIR_OUT, (void *) skb);

	/* Send the packet down the stack. */
	result = priv->chnl.dn->transmit(priv->chnl.dn, pkt);
	if (result) {
		dev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	/* Update statistics. */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;

	return NETDEV_TX_OK;
}
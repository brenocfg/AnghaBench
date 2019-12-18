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
struct sk_buff {scalar_t__ len; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
struct dsa_slave_priv {struct sk_buff* (* xmit ) (struct sk_buff*,struct net_device*) ;int /*<<< orphan*/  stats64; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int deferred_xmit; int /*<<< orphan*/ * clone; } ;

/* Variables and functions */
 TYPE_1__* DSA_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dsa_enqueue_skb (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  dsa_skb_tx_timestamp (struct dsa_slave_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 struct sk_buff* stub1 (struct sk_buff*,struct net_device*) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t dsa_slave_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct pcpu_sw_netstats *s;
	struct sk_buff *nskb;

	s = this_cpu_ptr(p->stats64);
	u64_stats_update_begin(&s->syncp);
	s->tx_packets++;
	s->tx_bytes += skb->len;
	u64_stats_update_end(&s->syncp);

	DSA_SKB_CB(skb)->deferred_xmit = false;
	DSA_SKB_CB(skb)->clone = NULL;

	/* Identify PTP protocol packets, clone them, and pass them to the
	 * switch driver
	 */
	dsa_skb_tx_timestamp(p, skb);

	/* Transmit function may have to reallocate the original SKB,
	 * in which case it must have freed it. Only free it here on error.
	 */
	nskb = p->xmit(skb, dev);
	if (!nskb) {
		if (!DSA_SKB_CB(skb)->deferred_xmit)
			kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	return dsa_enqueue_skb(nskb, dev);
}
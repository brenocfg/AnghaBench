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
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ len; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
struct dsa_slave_priv {struct sk_buff* (* xmit ) (struct sk_buff*,struct net_device*) ;int /*<<< orphan*/  stats64; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  dsa_skb_tx_timestamp (struct dsa_slave_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  dsa_slave_netpoll_send_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  dsa_slave_to_master (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netpoll_tx_running (struct net_device*) ; 
 struct sk_buff* stub1 (struct sk_buff*,struct net_device*) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

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

	/* Identify PTP protocol packets, clone them, and pass them to the
	 * switch driver
	 */
	dsa_skb_tx_timestamp(p, skb);

	/* Transmit function may have to reallocate the original SKB,
	 * in which case it must have freed it. Only free it here on error.
	 */
	nskb = p->xmit(skb, dev);
	if (!nskb) {
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	/* SKB for netpoll still need to be mangled with the protocol-specific
	 * tag to be successfully transmitted
	 */
	if (unlikely(netpoll_tx_running(dev)))
		return dsa_slave_netpoll_send_skb(dev, nskb);

	/* Queue the SKB for transmission on the parent interface, but
	 * do not modify its EtherType
	 */
	nskb->dev = dsa_slave_to_master(dev);
	dev_queue_xmit(nskb);

	return NETDEV_TX_OK;
}
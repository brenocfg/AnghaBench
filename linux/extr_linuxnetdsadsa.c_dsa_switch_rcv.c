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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct packet_type {int dummy; } ;
struct net_device {struct dsa_port* dsa_ptr; } ;
struct dsa_slave_priv {int /*<<< orphan*/  stats64; } ;
struct dsa_port {struct sk_buff* (* rcv ) (struct sk_buff*,struct net_device*,struct packet_type*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 scalar_t__ dsa_skb_defer_rx_timestamp (struct dsa_slave_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct dsa_slave_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct sk_buff*,struct net_device*,struct packet_type*) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dsa_switch_rcv(struct sk_buff *skb, struct net_device *dev,
			  struct packet_type *pt, struct net_device *unused)
{
	struct dsa_port *cpu_dp = dev->dsa_ptr;
	struct sk_buff *nskb = NULL;
	struct pcpu_sw_netstats *s;
	struct dsa_slave_priv *p;

	if (unlikely(!cpu_dp)) {
		kfree_skb(skb);
		return 0;
	}

	skb = skb_unshare(skb, GFP_ATOMIC);
	if (!skb)
		return 0;

	nskb = cpu_dp->rcv(skb, dev, pt);
	if (!nskb) {
		kfree_skb(skb);
		return 0;
	}

	skb = nskb;
	p = netdev_priv(skb->dev);
	skb_push(skb, ETH_HLEN);
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, skb->dev);

	s = this_cpu_ptr(p->stats64);
	u64_stats_update_begin(&s->syncp);
	s->rx_packets++;
	s->rx_bytes += skb->len;
	u64_stats_update_end(&s->syncp);

	if (dsa_skb_defer_rx_timestamp(p, skb))
		return 0;

	netif_receive_skb(skb);

	return 0;
}
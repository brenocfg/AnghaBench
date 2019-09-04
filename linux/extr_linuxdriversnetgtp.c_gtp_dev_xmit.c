#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_3__ stats; int /*<<< orphan*/  needed_headroom; } ;
struct TYPE_5__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct gtp_pktinfo {int /*<<< orphan*/  gtph_port; TYPE_4__* rt; TYPE_2__* iph; TYPE_1__ fl4; int /*<<< orphan*/  sk; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_8__ {int /*<<< orphan*/  dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_P_IP 128 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int gtp_build_skb_ip4 (struct sk_buff*,struct net_device*,struct gtp_pktinfo*) ; 
 int /*<<< orphan*/  ip4_dst_hoplimit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_inner_headers (struct sk_buff*) ; 
 int /*<<< orphan*/  udp_tunnel_xmit_skb (TYPE_4__*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static netdev_tx_t gtp_dev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	unsigned int proto = ntohs(skb->protocol);
	struct gtp_pktinfo pktinfo;
	int err;

	/* Ensure there is sufficient headroom. */
	if (skb_cow_head(skb, dev->needed_headroom))
		goto tx_err;

	skb_reset_inner_headers(skb);

	/* PDP context lookups in gtp_build_skb_*() need rcu read-side lock. */
	rcu_read_lock();
	switch (proto) {
	case ETH_P_IP:
		err = gtp_build_skb_ip4(skb, dev, &pktinfo);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}
	rcu_read_unlock();

	if (err < 0)
		goto tx_err;

	switch (proto) {
	case ETH_P_IP:
		netdev_dbg(pktinfo.dev, "gtp -> IP src: %pI4 dst: %pI4\n",
			   &pktinfo.iph->saddr, &pktinfo.iph->daddr);
		udp_tunnel_xmit_skb(pktinfo.rt, pktinfo.sk, skb,
				    pktinfo.fl4.saddr, pktinfo.fl4.daddr,
				    pktinfo.iph->tos,
				    ip4_dst_hoplimit(&pktinfo.rt->dst),
				    0,
				    pktinfo.gtph_port, pktinfo.gtph_port,
				    true, false);
		break;
	}

	return NETDEV_TX_OK;
tx_err:
	dev->stats.tx_errors++;
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}
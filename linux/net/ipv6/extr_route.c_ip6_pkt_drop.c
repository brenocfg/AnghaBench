#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {scalar_t__ loopback_dev; } ;
struct inet6_dev {int dummy; } ;
struct dst_entry {scalar_t__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  iif; } ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_DEST_UNREACH ; 
 TYPE_2__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,struct inet6_dev*,int) ; 
 int IPSTATS_MIB_INADDRERRORS ; 
#define  IPSTATS_MIB_INNOROUTES 129 
#define  IPSTATS_MIB_OUTNOROUTES 128 
 int IPV6_ADDR_ANY ; 
 struct inet6_dev* __in6_dev_get_safely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_by_index_rcu (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (scalar_t__) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet6_dev* ip6_dst_idev (struct dst_entry*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ netif_is_l3_master (int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 

__attribute__((used)) static int ip6_pkt_drop(struct sk_buff *skb, u8 code, int ipstats_mib_noroutes)
{
	struct dst_entry *dst = skb_dst(skb);
	struct net *net = dev_net(dst->dev);
	struct inet6_dev *idev;
	int type;

	if (netif_is_l3_master(skb->dev) &&
	    dst->dev == net->loopback_dev)
		idev = __in6_dev_get_safely(dev_get_by_index_rcu(net, IP6CB(skb)->iif));
	else
		idev = ip6_dst_idev(dst);

	switch (ipstats_mib_noroutes) {
	case IPSTATS_MIB_INNOROUTES:
		type = ipv6_addr_type(&ipv6_hdr(skb)->daddr);
		if (type == IPV6_ADDR_ANY) {
			IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDRERRORS);
			break;
		}
		/* FALLTHROUGH */
	case IPSTATS_MIB_OUTNOROUTES:
		IP6_INC_STATS(net, idev, ipstats_mib_noroutes);
		break;
	}

	/* Start over by dropping the dst for l3mdev case */
	if (netif_is_l3_master(skb->dev))
		skb_dst_drop(skb);

	icmpv6_send(skb, ICMPV6_DEST_UNREACH, code, 0);
	kfree_skb(skb);
	return 0;
}
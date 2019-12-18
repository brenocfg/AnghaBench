#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  daddr; } ;
struct inet6_skb_parm {int flags; scalar_t__ ra; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_8__ {TYPE_1__* devconf_all; } ;
struct TYPE_10__ {TYPE_2__ ipv6; } ;
struct TYPE_9__ {struct net_device* dev; } ;
struct TYPE_7__ {scalar_t__ mc_forwarding; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 int IP6SKB_FORWARDED ; 
 int IP6SKB_ROUTERALERT ; 
 int /*<<< orphan*/  IPSTATS_MIB_INMCAST ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_LOOPBACK ; 
 int /*<<< orphan*/  IPV6_OPT_ROUTERALERT_MLD ; 
 int /*<<< orphan*/  __IP6_UPD_PO_STATS (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __in6_dev_get_safely (struct net_device*) ; 
 struct net_device* dev_get_by_index_rcu (TYPE_4__*,int) ; 
 TYPE_4__* dev_net (struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int inet6_sdif (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_input (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_mr_input (struct sk_buff*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int ipv6_chk_mcast_addr (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_ext_hdr (int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_is_mld (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int ipv6_skip_exthdr (struct sk_buff*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int ip6_mc_input(struct sk_buff *skb)
{
	int sdif = inet6_sdif(skb);
	const struct ipv6hdr *hdr;
	struct net_device *dev;
	bool deliver;

	__IP6_UPD_PO_STATS(dev_net(skb_dst(skb)->dev),
			 __in6_dev_get_safely(skb->dev), IPSTATS_MIB_INMCAST,
			 skb->len);

	/* skb->dev passed may be master dev for vrfs. */
	if (sdif) {
		rcu_read_lock();
		dev = dev_get_by_index_rcu(dev_net(skb->dev), sdif);
		if (!dev) {
			rcu_read_unlock();
			kfree_skb(skb);
			return -ENODEV;
		}
	} else {
		dev = skb->dev;
	}

	hdr = ipv6_hdr(skb);
	deliver = ipv6_chk_mcast_addr(dev, &hdr->daddr, NULL);
	if (sdif)
		rcu_read_unlock();

#ifdef CONFIG_IPV6_MROUTE
	/*
	 *      IPv6 multicast router mode is now supported ;)
	 */
	if (dev_net(skb->dev)->ipv6.devconf_all->mc_forwarding &&
	    !(ipv6_addr_type(&hdr->daddr) &
	      (IPV6_ADDR_LOOPBACK|IPV6_ADDR_LINKLOCAL)) &&
	    likely(!(IP6CB(skb)->flags & IP6SKB_FORWARDED))) {
		/*
		 * Okay, we try to forward - split and duplicate
		 * packets.
		 */
		struct sk_buff *skb2;
		struct inet6_skb_parm *opt = IP6CB(skb);

		/* Check for MLD */
		if (unlikely(opt->flags & IP6SKB_ROUTERALERT)) {
			/* Check if this is a mld message */
			u8 nexthdr = hdr->nexthdr;
			__be16 frag_off;
			int offset;

			/* Check if the value of Router Alert
			 * is for MLD (0x0000).
			 */
			if (opt->ra == htons(IPV6_OPT_ROUTERALERT_MLD)) {
				deliver = false;

				if (!ipv6_ext_hdr(nexthdr)) {
					/* BUG */
					goto out;
				}
				offset = ipv6_skip_exthdr(skb, sizeof(*hdr),
							  &nexthdr, &frag_off);
				if (offset < 0)
					goto out;

				if (ipv6_is_mld(skb, nexthdr, offset))
					deliver = true;

				goto out;
			}
			/* unknown RA - process it normally */
		}

		if (deliver)
			skb2 = skb_clone(skb, GFP_ATOMIC);
		else {
			skb2 = skb;
			skb = NULL;
		}

		if (skb2) {
			ip6_mr_input(skb2);
		}
	}
out:
#endif
	if (likely(deliver))
		ip6_input(skb);
	else {
		/* discard */
		kfree_skb(skb);
	}

	return 0;
}
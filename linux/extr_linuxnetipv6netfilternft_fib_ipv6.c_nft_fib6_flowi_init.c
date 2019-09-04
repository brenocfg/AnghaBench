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
struct nft_pktinfo {TYPE_1__* skb; } ;
struct nft_fib {int flags; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct flowi6 {int flowlabel; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  daddr; } ;
typedef  int __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  mark; struct net_device const* dev; } ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_UNICAST ; 
 int IPV6_FLOWINFO_MASK ; 
 int NFTA_FIB_F_DADDR ; 
 int NFTA_FIB_F_MARK ; 
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int RT6_LOOKUP_F_IFACE ; 
 int /*<<< orphan*/  get_ifindex (struct net_device const*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nft_fib6_flowi_init(struct flowi6 *fl6, const struct nft_fib *priv,
			       const struct nft_pktinfo *pkt,
			       const struct net_device *dev,
			       struct ipv6hdr *iph)
{
	int lookup_flags = 0;

	if (priv->flags & NFTA_FIB_F_DADDR) {
		fl6->daddr = iph->daddr;
		fl6->saddr = iph->saddr;
	} else {
		fl6->daddr = iph->saddr;
		fl6->saddr = iph->daddr;
	}

	if (ipv6_addr_type(&fl6->daddr) & IPV6_ADDR_LINKLOCAL) {
		lookup_flags |= RT6_LOOKUP_F_IFACE;
		fl6->flowi6_oif = get_ifindex(dev ? dev : pkt->skb->dev);
	}

	if (ipv6_addr_type(&fl6->saddr) & IPV6_ADDR_UNICAST)
		lookup_flags |= RT6_LOOKUP_F_HAS_SADDR;

	if (priv->flags & NFTA_FIB_F_MARK)
		fl6->flowi6_mark = pkt->skb->mark;

	fl6->flowlabel = (*(__be32 *)iph) & IPV6_FLOWINFO_MASK;

	return lookup_flags;
}
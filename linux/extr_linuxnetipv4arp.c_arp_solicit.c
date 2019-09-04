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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int priv_flags; int /*<<< orphan*/  dev_addr; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  parms; int /*<<< orphan*/  probes; scalar_t__ primary_key; struct net_device* dev; } ;
struct in_device {int dummy; } ;
struct dst_entry {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {scalar_t__ saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_PROBES ; 
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int IFF_XMIT_DST_RELEASE ; 
 int IN_DEV_ARP_ANNOUNCE (struct in_device*) ; 
 int MAX_ADDR_LEN ; 
 scalar_t__ NEIGH_VAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  RTN_LOCAL ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  UCAST_PROBES ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  arp_send_dst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct net_device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dst_entry*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  inet_addr_onlink (struct in_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  inet_addr_type_dev_table (int /*<<< orphan*/ ,struct net_device*,scalar_t__) ; 
 scalar_t__ inet_select_addr (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_app_ns (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_ha_snapshot (int /*<<< orphan*/ *,struct neighbour*,struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static void arp_solicit(struct neighbour *neigh, struct sk_buff *skb)
{
	__be32 saddr = 0;
	u8 dst_ha[MAX_ADDR_LEN], *dst_hw = NULL;
	struct net_device *dev = neigh->dev;
	__be32 target = *(__be32 *)neigh->primary_key;
	int probes = atomic_read(&neigh->probes);
	struct in_device *in_dev;
	struct dst_entry *dst = NULL;

	rcu_read_lock();
	in_dev = __in_dev_get_rcu(dev);
	if (!in_dev) {
		rcu_read_unlock();
		return;
	}
	switch (IN_DEV_ARP_ANNOUNCE(in_dev)) {
	default:
	case 0:		/* By default announce any local IP */
		if (skb && inet_addr_type_dev_table(dev_net(dev), dev,
					  ip_hdr(skb)->saddr) == RTN_LOCAL)
			saddr = ip_hdr(skb)->saddr;
		break;
	case 1:		/* Restrict announcements of saddr in same subnet */
		if (!skb)
			break;
		saddr = ip_hdr(skb)->saddr;
		if (inet_addr_type_dev_table(dev_net(dev), dev,
					     saddr) == RTN_LOCAL) {
			/* saddr should be known to target */
			if (inet_addr_onlink(in_dev, target, saddr))
				break;
		}
		saddr = 0;
		break;
	case 2:		/* Avoid secondary IPs, get a primary/preferred one */
		break;
	}
	rcu_read_unlock();

	if (!saddr)
		saddr = inet_select_addr(dev, target, RT_SCOPE_LINK);

	probes -= NEIGH_VAR(neigh->parms, UCAST_PROBES);
	if (probes < 0) {
		if (!(neigh->nud_state & NUD_VALID))
			pr_debug("trying to ucast probe in NUD_INVALID\n");
		neigh_ha_snapshot(dst_ha, neigh, dev);
		dst_hw = dst_ha;
	} else {
		probes -= NEIGH_VAR(neigh->parms, APP_PROBES);
		if (probes < 0) {
			neigh_app_ns(neigh);
			return;
		}
	}

	if (skb && !(dev->priv_flags & IFF_XMIT_DST_RELEASE))
		dst = skb_dst(skb);
	arp_send_dst(ARPOP_REQUEST, ETH_P_ARP, target, dev, saddr,
		     dst_hw, dev->dev_addr, NULL, dst);
}
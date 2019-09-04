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
typedef  scalar_t__ u8 ;
struct tnl_ptk_info {int /*<<< orphan*/  proto; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct metadata_dst {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_2__ {scalar_t__ collect_md; int /*<<< orphan*/  proto; } ;
struct ip6_tnl {TYPE_1__ parms; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int __ip6_tnl_rcv (struct ip6_tnl*,struct sk_buff*,struct tnl_ptk_info const*,struct metadata_dst*,int (*) (struct ip6_tnl const*,struct ipv6hdr const*,struct sk_buff*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 struct ip6_tnl* ip6_tnl_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_tnl_rcv_ctl (struct ip6_tnl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ iptunnel_pull_header (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 struct metadata_dst* ipv6_tun_rx_dst (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  log_ecn_error ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  xfrm6_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int ipxip6_rcv(struct sk_buff *skb, u8 ipproto,
		      const struct tnl_ptk_info *tpi,
		      int (*dscp_ecn_decapsulate)(const struct ip6_tnl *t,
						  const struct ipv6hdr *ipv6h,
						  struct sk_buff *skb))
{
	struct ip6_tnl *t;
	const struct ipv6hdr *ipv6h = ipv6_hdr(skb);
	struct metadata_dst *tun_dst = NULL;
	int ret = -1;

	rcu_read_lock();
	t = ip6_tnl_lookup(dev_net(skb->dev), &ipv6h->saddr, &ipv6h->daddr);

	if (t) {
		u8 tproto = READ_ONCE(t->parms.proto);

		if (tproto != ipproto && tproto != 0)
			goto drop;
		if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb))
			goto drop;
		ipv6h = ipv6_hdr(skb);
		if (!ip6_tnl_rcv_ctl(t, &ipv6h->daddr, &ipv6h->saddr))
			goto drop;
		if (iptunnel_pull_header(skb, 0, tpi->proto, false))
			goto drop;
		if (t->parms.collect_md) {
			tun_dst = ipv6_tun_rx_dst(skb, 0, 0, 0);
			if (!tun_dst)
				goto drop;
		}
		ret = __ip6_tnl_rcv(t, skb, tpi, tun_dst, dscp_ecn_decapsulate,
				    log_ecn_error);
	}

	rcu_read_unlock();

	return ret;

drop:
	rcu_read_unlock();
	kfree_skb(skb);
	return 0;
}
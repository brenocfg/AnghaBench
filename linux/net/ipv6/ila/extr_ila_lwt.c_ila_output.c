#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct rt6_info {int rt6i_flags; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct ila_lwt {int /*<<< orphan*/  dst_cache; scalar_t__ connected; scalar_t__ lwt_output; } ;
struct flowi6 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi6_iif; int /*<<< orphan*/  flowi6_oif; } ;
struct dst_entry {scalar_t__ error; TYPE_1__* dev; TYPE_2__* lwtstate; } ;
typedef  int /*<<< orphan*/  fl6 ;
struct TYPE_5__ {int (* orig_output ) (struct net*,struct sock*,struct sk_buff*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int PTR_ERR (struct dst_entry*) ; 
 int RTF_CACHE ; 
 int RTF_GATEWAY ; 
 struct dst_entry* dst_cache_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_cache_set_ip6 (int /*<<< orphan*/ *,struct dst_entry*,int /*<<< orphan*/ *) ; 
 int dst_output (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ila_lwt* ila_lwt_lwtunnel (TYPE_2__*) ; 
 int /*<<< orphan*/  ila_params_lwtunnel (TYPE_2__*) ; 
 int /*<<< orphan*/  ila_update_ipv6_locator (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct dst_entry* ip6_route_output (struct net*,int /*<<< orphan*/ *,struct flowi6*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * rt6_nexthop (struct rt6_info*,int /*<<< orphan*/ *) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int stub1 (struct net*,struct sock*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 struct dst_entry* xfrm_lookup (struct net*,struct dst_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ila_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct dst_entry *orig_dst = skb_dst(skb);
	struct rt6_info *rt = (struct rt6_info *)orig_dst;
	struct ila_lwt *ilwt = ila_lwt_lwtunnel(orig_dst->lwtstate);
	struct dst_entry *dst;
	int err = -EINVAL;

	if (skb->protocol != htons(ETH_P_IPV6))
		goto drop;

	if (ilwt->lwt_output)
		ila_update_ipv6_locator(skb,
					ila_params_lwtunnel(orig_dst->lwtstate),
					true);

	if (rt->rt6i_flags & (RTF_GATEWAY | RTF_CACHE)) {
		/* Already have a next hop address in route, no need for
		 * dest cache route.
		 */
		return orig_dst->lwtstate->orig_output(net, sk, skb);
	}

	dst = dst_cache_get(&ilwt->dst_cache);
	if (unlikely(!dst)) {
		struct ipv6hdr *ip6h = ipv6_hdr(skb);
		struct flowi6 fl6;

		/* Lookup a route for the new destination. Take into
		 * account that the base route may already have a gateway.
		 */

		memset(&fl6, 0, sizeof(fl6));
		fl6.flowi6_oif = orig_dst->dev->ifindex;
		fl6.flowi6_iif = LOOPBACK_IFINDEX;
		fl6.daddr = *rt6_nexthop((struct rt6_info *)orig_dst,
					 &ip6h->daddr);

		dst = ip6_route_output(net, NULL, &fl6);
		if (dst->error) {
			err = -EHOSTUNREACH;
			dst_release(dst);
			goto drop;
		}

		dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), NULL, 0);
		if (IS_ERR(dst)) {
			err = PTR_ERR(dst);
			goto drop;
		}

		if (ilwt->connected)
			dst_cache_set_ip6(&ilwt->dst_cache, dst, &fl6.saddr);
	}

	skb_dst_set(skb, dst);
	return dst_output(net, sk, skb);

drop:
	kfree_skb(skb);
	return err;
}
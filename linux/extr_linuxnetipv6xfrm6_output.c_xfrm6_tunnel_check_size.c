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
struct sk_buff {int len; scalar_t__ sk; int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; scalar_t__ ignore_df; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ICMPV6_PKT_TOOBIG ; 
 int IPV6_MIN_MTU ; 
 int dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ip6_skb_dst_mtu (struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gso_validate_network_len (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ xfrm6_local_dontfrag (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm6_local_rxpmtu (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xfrm_local_error (struct sk_buff*,int) ; 

__attribute__((used)) static int xfrm6_tunnel_check_size(struct sk_buff *skb)
{
	int mtu, ret = 0;
	struct dst_entry *dst = skb_dst(skb);

	if (skb->ignore_df)
		goto out;

	mtu = dst_mtu(dst);
	if (mtu < IPV6_MIN_MTU)
		mtu = IPV6_MIN_MTU;

	if ((!skb_is_gso(skb) && skb->len > mtu) ||
	    (skb_is_gso(skb) &&
	     !skb_gso_validate_network_len(skb, ip6_skb_dst_mtu(skb)))) {
		skb->dev = dst->dev;
		skb->protocol = htons(ETH_P_IPV6);

		if (xfrm6_local_dontfrag(skb))
			xfrm6_local_rxpmtu(skb, mtu);
		else if (skb->sk)
			xfrm_local_error(skb, mtu);
		else
			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		ret = -EMSGSIZE;
	}
out:
	return ret;
}
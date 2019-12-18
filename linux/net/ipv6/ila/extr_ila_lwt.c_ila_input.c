#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ protocol; } ;
struct ila_lwt {int /*<<< orphan*/  lwt_output; } ;
struct dst_entry {TYPE_1__* lwtstate; } ;
struct TYPE_3__ {int (* orig_input ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ila_lwt* ila_lwt_lwtunnel (TYPE_1__*) ; 
 int /*<<< orphan*/  ila_params_lwtunnel (TYPE_1__*) ; 
 int /*<<< orphan*/  ila_update_ipv6_locator (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 

__attribute__((used)) static int ila_input(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct ila_lwt *ilwt = ila_lwt_lwtunnel(dst->lwtstate);

	if (skb->protocol != htons(ETH_P_IPV6))
		goto drop;

	if (!ilwt->lwt_output)
		ila_update_ipv6_locator(skb,
					ila_params_lwtunnel(dst->lwtstate),
					false);

	return dst->lwtstate->orig_input(skb);

drop:
	kfree_skb(skb);
	return -EINVAL;
}
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
struct sk_buff {int dummy; } ;
struct nf_hook_state {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {struct in6_addr daddr; } ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 unsigned int NF_STOLEN ; 
 scalar_t__ ipv6_addr_cmp (struct in6_addr*,struct in6_addr*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 unsigned int nf_nat_ipv6_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 

__attribute__((used)) static unsigned int
nf_nat_ipv6_in(void *priv, struct sk_buff *skb,
	       const struct nf_hook_state *state)
{
	unsigned int ret;
	struct in6_addr daddr = ipv6_hdr(skb)->daddr;

	ret = nf_nat_ipv6_fn(priv, skb, state);
	if (ret != NF_DROP && ret != NF_STOLEN &&
	    ipv6_addr_cmp(&daddr, &ipv6_hdr(skb)->daddr))
		skb_dst_drop(skb);

	return ret;
}
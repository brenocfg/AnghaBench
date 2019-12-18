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
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {scalar_t__ daddr; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 unsigned int nf_nat_ipv4_fn (void*,struct sk_buff*,struct nf_hook_state const*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 

__attribute__((used)) static unsigned int
nf_nat_ipv4_in(void *priv, struct sk_buff *skb,
	       const struct nf_hook_state *state)
{
	unsigned int ret;
	__be32 daddr = ip_hdr(skb)->daddr;

	ret = nf_nat_ipv4_fn(priv, skb, state);
	if (ret == NF_ACCEPT && daddr != ip_hdr(skb)->daddr)
		skb_dst_drop(skb);

	return ret;
}
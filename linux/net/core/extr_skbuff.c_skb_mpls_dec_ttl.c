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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  label_stack_entry; } ;

/* Variables and functions */
 int EINVAL ; 
 int MPLS_LS_TTL_MASK ; 
 int MPLS_LS_TTL_SHIFT ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  eth_p_mpls (int /*<<< orphan*/ ) ; 
 TYPE_1__* mpls_hdr (struct sk_buff*) ; 
 int skb_mpls_update_lse (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int skb_mpls_dec_ttl(struct sk_buff *skb)
{
	u32 lse;
	u8 ttl;

	if (unlikely(!eth_p_mpls(skb->protocol)))
		return -EINVAL;

	lse = be32_to_cpu(mpls_hdr(skb)->label_stack_entry);
	ttl = (lse & MPLS_LS_TTL_MASK) >> MPLS_LS_TTL_SHIFT;
	if (!--ttl)
		return -EINVAL;

	lse &= ~MPLS_LS_TTL_MASK;
	lse |= ttl << MPLS_LS_TTL_SHIFT;

	return skb_mpls_update_lse(skb, cpu_to_be32(lse));
}
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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {scalar_t__ frag_max_size; } ;

/* Variables and functions */
 TYPE_1__* IP6CB (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff const*) ; 

__attribute__((used)) static inline bool
__mtu_check_toobig_v6(const struct sk_buff *skb, u32 mtu)
{
	if (IP6CB(skb)->frag_max_size) {
		/* frag_max_size tell us that, this packet have been
		 * defragmented by netfilter IPv6 conntrack module.
		 */
		if (IP6CB(skb)->frag_max_size > mtu)
			return true; /* largest fragment violate MTU */
	}
	else if (skb->len > mtu && !skb_is_gso(skb)) {
		return true; /* Packet size violate MTU size */
	}
	return false;
}
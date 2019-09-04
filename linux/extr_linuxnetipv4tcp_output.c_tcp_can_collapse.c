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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int sacked; } ;

/* Variables and functions */
 int TCPCB_SACKED_ACKED ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 scalar_t__ skb_cloned (struct sk_buff const*) ; 
 int tcp_skb_pcount (struct sk_buff const*) ; 

__attribute__((used)) static bool tcp_can_collapse(const struct sock *sk, const struct sk_buff *skb)
{
	if (tcp_skb_pcount(skb) > 1)
		return false;
	if (skb_cloned(skb))
		return false;
	/* Some heuristics for collapsing over SACK'd could be invented */
	if (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED)
		return false;

	return true;
}
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
struct tcp_sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int sacked; } ;

/* Variables and functions */
 int TCPCB_RETRANS ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 int /*<<< orphan*/  tcp_skb_timestamp (struct sk_buff const*) ; 
 scalar_t__ tcp_tsopt_ecr_before (struct tcp_sock const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tcp_skb_spurious_retrans(const struct tcp_sock *tp,
				     const struct sk_buff *skb)
{
	return (TCP_SKB_CB(skb)->sacked & TCPCB_RETRANS) &&
	       tcp_tsopt_ecr_before(tp, tcp_skb_timestamp(skb));
}
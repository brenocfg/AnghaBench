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
struct tcp_sock {int /*<<< orphan*/  lost; } ;
struct sk_buff {int dummy; } ;
typedef  int __u8 ;
struct TYPE_2__ {int sacked; } ;

/* Variables and functions */
 int TCPCB_LOST ; 
 int TCPCB_SACKED_RETRANS ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ tcp_skb_pcount (struct sk_buff*) ; 

__attribute__((used)) static void tcp_sum_lost(struct tcp_sock *tp, struct sk_buff *skb)
{
	__u8 sacked = TCP_SKB_CB(skb)->sacked;

	if (!(sacked & TCPCB_LOST) ||
	    ((sacked & TCPCB_LOST) && (sacked & TCPCB_SACKED_RETRANS)))
		tp->lost += tcp_skb_pcount(skb);
}
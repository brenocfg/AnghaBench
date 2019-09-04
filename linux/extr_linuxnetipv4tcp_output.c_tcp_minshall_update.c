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
struct tcp_sock {int /*<<< orphan*/  snd_sml; } ;
struct sk_buff {unsigned int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  end_seq; } ;

/* Variables and functions */
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 unsigned int tcp_skb_pcount (struct sk_buff const*) ; 

__attribute__((used)) static void tcp_minshall_update(struct tcp_sock *tp, unsigned int mss_now,
				const struct sk_buff *skb)
{
	if (skb->len < tcp_skb_pcount(skb) * mss_now)
		tp->snd_sml = TCP_SKB_CB(skb)->end_seq;
}
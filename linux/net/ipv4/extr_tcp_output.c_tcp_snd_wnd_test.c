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
struct tcp_sock {int dummy; } ;
struct sk_buff {unsigned int len; } ;
struct TYPE_2__ {scalar_t__ seq; scalar_t__ end_seq; } ;

/* Variables and functions */
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 int /*<<< orphan*/  after (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_wnd_end (struct tcp_sock const*) ; 

__attribute__((used)) static bool tcp_snd_wnd_test(const struct tcp_sock *tp,
			     const struct sk_buff *skb,
			     unsigned int cur_mss)
{
	u32 end_seq = TCP_SKB_CB(skb)->end_seq;

	if (skb->len > cur_mss)
		end_seq = TCP_SKB_CB(skb)->seq + cur_mss;

	return !after(end_seq, tcp_wnd_end(tp));
}
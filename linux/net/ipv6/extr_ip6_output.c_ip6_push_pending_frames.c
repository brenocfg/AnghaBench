#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct sk_buff* ip6_finish_skb (struct sock*) ; 
 int ip6_send_skb (struct sk_buff*) ; 

int ip6_push_pending_frames(struct sock *sk)
{
	struct sk_buff *skb;

	skb = ip6_finish_skb(sk);
	if (!skb)
		return 0;

	return ip6_send_skb(skb);
}
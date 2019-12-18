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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  pipe_grant_credits (struct sock*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

struct sk_buff *pep_read(struct sock *sk)
{
	struct sk_buff *skb = skb_dequeue(&sk->sk_receive_queue);

	if (sk->sk_state == TCP_ESTABLISHED)
		pipe_grant_credits(sk, GFP_ATOMIC);
	return skb;
}
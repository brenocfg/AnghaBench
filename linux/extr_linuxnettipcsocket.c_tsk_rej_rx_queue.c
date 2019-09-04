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
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_ERR_NO_PORT ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_sk_respond (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsk_rej_rx_queue(struct sock *sk)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(&sk->sk_receive_queue)))
		tipc_sk_respond(sk, skb, TIPC_ERR_NO_PORT);
}
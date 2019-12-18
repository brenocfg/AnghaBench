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
struct tipc_sock {scalar_t__ cong_link_cnt; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_timer; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_msg_skb_clone (int /*<<< orphan*/ *,struct sk_buff_head*) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 

__attribute__((used)) static void tipc_sk_retry_connect(struct sock *sk, struct sk_buff_head *list)
{
	struct tipc_sock *tsk = tipc_sk(sk);

	/* Try again later if dest link is congested */
	if (tsk->cong_link_cnt) {
		sk_reset_timer(sk, &sk->sk_timer, msecs_to_jiffies(100));
		return;
	}
	/* Prepare SYN for retransmit */
	tipc_msg_skb_clone(&sk->sk_write_queue, list);
}
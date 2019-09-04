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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlink_deliver_tap (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int __netlink_sendskb(struct sock *sk, struct sk_buff *skb)
{
	int len = skb->len;

	netlink_deliver_tap(sock_net(sk), skb);

	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk);
	return len;
}
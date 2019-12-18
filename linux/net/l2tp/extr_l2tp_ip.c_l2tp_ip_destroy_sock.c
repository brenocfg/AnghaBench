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
struct sock {int /*<<< orphan*/  sk_write_queue; struct l2tp_tunnel* sk_user_data; } ;
struct sk_buff {int dummy; } ;
struct l2tp_tunnel {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2tp_tunnel_delete (struct l2tp_tunnel*) ; 

__attribute__((used)) static void l2tp_ip_destroy_sock(struct sock *sk)
{
	struct sk_buff *skb;
	struct l2tp_tunnel *tunnel = sk->sk_user_data;

	while ((skb = __skb_dequeue_tail(&sk->sk_write_queue)) != NULL)
		kfree_skb(skb);

	if (tunnel)
		l2tp_tunnel_delete(tunnel);
}
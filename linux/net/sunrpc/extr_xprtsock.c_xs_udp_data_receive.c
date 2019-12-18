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
struct sock_xprt {int /*<<< orphan*/  recv_mutex; int /*<<< orphan*/  xprt; struct sock* inet; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_recv_udp (struct sock*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  xs_poll_check_readable (struct sock_xprt*) ; 
 int /*<<< orphan*/  xs_udp_data_read_skb (int /*<<< orphan*/ *,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void xs_udp_data_receive(struct sock_xprt *transport)
{
	struct sk_buff *skb;
	struct sock *sk;
	int err;

	mutex_lock(&transport->recv_mutex);
	sk = transport->inet;
	if (sk == NULL)
		goto out;
	for (;;) {
		skb = skb_recv_udp(sk, 0, 1, &err);
		if (skb == NULL)
			break;
		xs_udp_data_read_skb(&transport->xprt, sk, skb);
		consume_skb(skb);
		cond_resched();
	}
	xs_poll_check_readable(transport);
out:
	mutex_unlock(&transport->recv_mutex);
}
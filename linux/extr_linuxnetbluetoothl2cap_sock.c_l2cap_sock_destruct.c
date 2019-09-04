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
struct sock {int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rx_busy_skb; scalar_t__ chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_chan_put (scalar_t__) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_sock_destruct(struct sock *sk)
{
	BT_DBG("sk %p", sk);

	if (l2cap_pi(sk)->chan)
		l2cap_chan_put(l2cap_pi(sk)->chan);

	if (l2cap_pi(sk)->rx_busy_skb) {
		kfree_skb(l2cap_pi(sk)->rx_busy_skb);
		l2cap_pi(sk)->rx_busy_skb = NULL;
	}

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_write_queue);
}
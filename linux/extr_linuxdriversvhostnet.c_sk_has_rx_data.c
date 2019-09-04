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
struct socket {TYPE_1__* ops; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; struct socket* sk_socket; } ;
struct TYPE_2__ {int (* peek_len ) (struct socket*) ;} ;

/* Variables and functions */
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 int stub1 (struct socket*) ; 

__attribute__((used)) static int sk_has_rx_data(struct sock *sk)
{
	struct socket *sock = sk->sk_socket;

	if (sock->ops->peek_len)
		return sock->ops->peek_len(sock);

	return skb_queue_empty(&sk->sk_receive_queue);
}
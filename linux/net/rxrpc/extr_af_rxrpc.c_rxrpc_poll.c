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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct rxrpc_sock {int /*<<< orphan*/  recvmsg_q; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct rxrpc_sock* rxrpc_sk (struct sock*) ; 
 scalar_t__ rxrpc_writable (struct sock*) ; 
 int /*<<< orphan*/  sock_poll_wait (struct file*,struct socket*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t rxrpc_poll(struct file *file, struct socket *sock,
			       poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct rxrpc_sock *rx = rxrpc_sk(sk);
	__poll_t mask;

	sock_poll_wait(file, sock, wait);
	mask = 0;

	/* the socket is readable if there are any messages waiting on the Rx
	 * queue */
	if (!list_empty(&rx->recvmsg_q))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* the socket is writable if there is space to add new data to the
	 * socket; there is no guarantee that any particular call in progress
	 * on the socket may have space in the Tx ACK window */
	if (rxrpc_writable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM;

	return mask;
}
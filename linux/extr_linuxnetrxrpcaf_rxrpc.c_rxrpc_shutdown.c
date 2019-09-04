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
struct socket {struct sock* sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sock {scalar_t__ sk_state; TYPE_1__ sk_receive_queue; int /*<<< orphan*/  sk_shutdown; } ;
struct rxrpc_sock {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ESHUTDOWN ; 
 scalar_t__ RXRPC_CLOSE ; 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int SHUT_RDWR ; 
 int /*<<< orphan*/  _enter (char*,struct sock*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  rxrpc_discard_prealloc (struct rxrpc_sock*) ; 
 struct rxrpc_sock* rxrpc_sk (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_shutdown(struct socket *sock, int flags)
{
	struct sock *sk = sock->sk;
	struct rxrpc_sock *rx = rxrpc_sk(sk);
	int ret = 0;

	_enter("%p,%d", sk, flags);

	if (flags != SHUT_RDWR)
		return -EOPNOTSUPP;
	if (sk->sk_state == RXRPC_CLOSE)
		return -ESHUTDOWN;

	lock_sock(sk);

	spin_lock_bh(&sk->sk_receive_queue.lock);
	if (sk->sk_state < RXRPC_CLOSE) {
		sk->sk_state = RXRPC_CLOSE;
		sk->sk_shutdown = SHUTDOWN_MASK;
	} else {
		ret = -ESHUTDOWN;
	}
	spin_unlock_bh(&sk->sk_receive_queue.lock);

	rxrpc_discard_prealloc(rx);

	release_sock(sk);
	return ret;
}
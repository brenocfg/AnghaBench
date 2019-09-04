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
struct socket_wq {int /*<<< orphan*/  flags; } ;
struct sock {int /*<<< orphan*/  sk_wq; TYPE_1__* sk_socket; } ;
struct rpc_xprt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct socket_wq* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct rpc_xprt* xprt_from_sock (struct sock*) ; 
 int /*<<< orphan*/  xprt_write_space (struct rpc_xprt*) ; 

__attribute__((used)) static void xs_write_space(struct sock *sk)
{
	struct socket_wq *wq;
	struct rpc_xprt *xprt;

	if (!sk->sk_socket)
		return;
	clear_bit(SOCK_NOSPACE, &sk->sk_socket->flags);

	if (unlikely(!(xprt = xprt_from_sock(sk))))
		return;
	rcu_read_lock();
	wq = rcu_dereference(sk->sk_wq);
	if (!wq || test_and_clear_bit(SOCKWQ_ASYNC_NOSPACE, &wq->flags) == 0)
		goto out;

	xprt_write_space(xprt);
out:
	rcu_read_unlock();
}
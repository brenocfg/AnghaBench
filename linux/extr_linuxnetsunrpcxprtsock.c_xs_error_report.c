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
struct sock {int sk_err; int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_socket; } ;
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rpc_socket_error (struct rpc_xprt*,int /*<<< orphan*/ ,int) ; 
 struct rpc_xprt* xprt_from_sock (struct sock*) ; 
 int /*<<< orphan*/  xprt_wake_pending_tasks (struct rpc_xprt*,int) ; 

__attribute__((used)) static void xs_error_report(struct sock *sk)
{
	struct rpc_xprt *xprt;
	int err;

	read_lock_bh(&sk->sk_callback_lock);
	if (!(xprt = xprt_from_sock(sk)))
		goto out;

	err = -sk->sk_err;
	if (err == 0)
		goto out;
	dprintk("RPC:       xs_error_report client %p, error=%d...\n",
			xprt, -err);
	trace_rpc_socket_error(xprt, sk->sk_socket, err);
	xprt_wake_pending_tasks(xprt, err);
 out:
	read_unlock_bh(&sk->sk_callback_lock);
}
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
struct socket {int dummy; } ;
struct rpc_xprt {int /*<<< orphan*/  swapper; } ;
struct sock_xprt {int /*<<< orphan*/  recv_mutex; struct file* file; struct socket* sock; struct sock* inet; struct rpc_xprt xprt; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/ * sk_user_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_clear_memalloc (struct sock*) ; 
 int /*<<< orphan*/  trace_rpc_socket_close (struct rpc_xprt*,struct socket*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_clear_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_disconnect_done (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xs_restore_old_callbacks (struct sock_xprt*,struct sock*) ; 
 int /*<<< orphan*/  xs_sock_reset_connection_flags (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xs_stream_reset_connect (struct sock_xprt*) ; 

__attribute__((used)) static void xs_reset_transport(struct sock_xprt *transport)
{
	struct socket *sock = transport->sock;
	struct sock *sk = transport->inet;
	struct rpc_xprt *xprt = &transport->xprt;
	struct file *filp = transport->file;

	if (sk == NULL)
		return;

	if (atomic_read(&transport->xprt.swapper))
		sk_clear_memalloc(sk);

	kernel_sock_shutdown(sock, SHUT_RDWR);

	mutex_lock(&transport->recv_mutex);
	write_lock_bh(&sk->sk_callback_lock);
	transport->inet = NULL;
	transport->sock = NULL;
	transport->file = NULL;

	sk->sk_user_data = NULL;

	xs_restore_old_callbacks(transport, sk);
	xprt_clear_connected(xprt);
	write_unlock_bh(&sk->sk_callback_lock);
	xs_sock_reset_connection_flags(xprt);
	/* Reset stream record info */
	xs_stream_reset_connect(transport);
	mutex_unlock(&transport->recv_mutex);

	trace_rpc_socket_close(xprt, sock);
	fput(filp);

	xprt_disconnect_done(xprt);
}
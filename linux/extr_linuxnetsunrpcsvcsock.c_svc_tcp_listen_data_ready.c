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
struct TYPE_2__ {int /*<<< orphan*/  xpt_flags; } ;
struct svc_sock {TYPE_1__ sk_xprt; int /*<<< orphan*/  (* sk_odata ) (struct sock*) ;} ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_user_data; } ;

/* Variables and functions */
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  XPT_CONN ; 
 int /*<<< orphan*/  dprintk (char*,struct sock*,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,struct sock*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (TYPE_1__*) ; 

__attribute__((used)) static void svc_tcp_listen_data_ready(struct sock *sk)
{
	struct svc_sock	*svsk = (struct svc_sock *)sk->sk_user_data;

	dprintk("svc: socket %p TCP (listen) state change %d\n",
		sk, sk->sk_state);

	if (svsk) {
		/* Refer to svc_setup_socket() for details. */
		rmb();
		svsk->sk_odata(sk);
	}

	/*
	 * This callback may called twice when a new connection
	 * is established as a child socket inherits everything
	 * from a parent LISTEN socket.
	 * 1) data_ready method of the parent socket will be called
	 *    when one of child sockets become ESTABLISHED.
	 * 2) data_ready method of the child socket may be called
	 *    when it receives data before the socket is accepted.
	 * In case of 2, we should ignore it silently.
	 */
	if (sk->sk_state == TCP_LISTEN) {
		if (svsk) {
			set_bit(XPT_CONN, &svsk->sk_xprt.xpt_flags);
			svc_xprt_enqueue(&svsk->sk_xprt);
		} else
			printk("svc: socket %p: no user data\n", sk);
	}
}
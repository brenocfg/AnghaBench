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
struct svc_sock {TYPE_1__ sk_xprt; int /*<<< orphan*/  (* sk_ostate ) (struct sock*) ;} ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_user_data; } ;

/* Variables and functions */
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  dprintk (char*,struct sock*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,struct sock*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (TYPE_1__*) ; 

__attribute__((used)) static void svc_tcp_state_change(struct sock *sk)
{
	struct svc_sock	*svsk = (struct svc_sock *)sk->sk_user_data;

	dprintk("svc: socket %p TCP (connected) state change %d (svsk %p)\n",
		sk, sk->sk_state, sk->sk_user_data);

	if (!svsk)
		printk("svc: socket %p: no user data\n", sk);
	else {
		/* Refer to svc_setup_socket() for details. */
		rmb();
		svsk->sk_ostate(sk);
		if (sk->sk_state != TCP_ESTABLISHED) {
			set_bit(XPT_CLOSE, &svsk->sk_xprt.xpt_flags);
			svc_xprt_enqueue(&svsk->sk_xprt);
		}
	}
}
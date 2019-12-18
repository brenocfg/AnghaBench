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
struct sock {scalar_t__ sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_BUSY ; 
 int /*<<< orphan*/  XPT_DATA ; 
 int /*<<< orphan*/  dprintk (char*,struct svc_sock*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (TYPE_1__*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void svc_data_ready(struct sock *sk)
{
	struct svc_sock	*svsk = (struct svc_sock *)sk->sk_user_data;

	if (svsk) {
		dprintk("svc: socket %p(inet %p), busy=%d\n",
			svsk, sk,
			test_bit(XPT_BUSY, &svsk->sk_xprt.xpt_flags));

		/* Refer to svc_setup_socket() for details. */
		rmb();
		svsk->sk_odata(sk);
		if (!test_and_set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags))
			svc_xprt_enqueue(&svsk->sk_xprt);
	}
}
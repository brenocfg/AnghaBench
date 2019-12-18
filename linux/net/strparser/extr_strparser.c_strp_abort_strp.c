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
struct strparser {int stopped; struct sock* sk; int /*<<< orphan*/  msg_timer_work; } ;
struct sock {int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void strp_abort_strp(struct strparser *strp, int err)
{
	/* Unrecoverable error in receive */

	cancel_delayed_work(&strp->msg_timer_work);

	if (strp->stopped)
		return;

	strp->stopped = 1;

	if (strp->sk) {
		struct sock *sk = strp->sk;

		/* Report an error on the lower socket */
		sk->sk_err = -err;
		sk->sk_error_report(sk);
	}
}
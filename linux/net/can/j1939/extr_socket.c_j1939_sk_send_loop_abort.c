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
struct sock {int sk_err; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void j1939_sk_send_loop_abort(struct sock *sk, int err)
{
	sk->sk_err = err;

	sk->sk_error_report(sk);
}
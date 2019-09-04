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
 int /*<<< orphan*/  __udp_disconnect (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int raw_abort(struct sock *sk, int err)
{
	lock_sock(sk);

	sk->sk_err = err;
	sk->sk_error_report(sk);
	__udp_disconnect(sk, 0);

	release_sock(sk);

	return 0;
}
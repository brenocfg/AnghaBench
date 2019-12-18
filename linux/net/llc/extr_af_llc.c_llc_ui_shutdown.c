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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_rcvtimeo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int llc_send_disc (struct sock*) ; 
 int llc_ui_wait_for_disc (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int llc_ui_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	int rc = -ENOTCONN;

	lock_sock(sk);
	if (unlikely(sk->sk_state != TCP_ESTABLISHED))
		goto out;
	rc = -EINVAL;
	if (how != 2)
		goto out;
	rc = llc_send_disc(sk);
	if (!rc)
		rc = llc_ui_wait_for_disc(sk, sk->sk_rcvtimeo);
	/* Wake up anyone sleeping in poll */
	sk->sk_state_change(sk);
out:
	release_sock(sk);
	return rc;
}
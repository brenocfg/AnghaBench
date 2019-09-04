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
struct sock {scalar_t__ sk_type; scalar_t__ sk_state; int sk_max_ack_backlog; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ SOCK_SEQPACKET ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int ax25_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	int res = 0;

	lock_sock(sk);
	if (sk->sk_type == SOCK_SEQPACKET && sk->sk_state != TCP_LISTEN) {
		sk->sk_max_ack_backlog = backlog;
		sk->sk_state           = TCP_LISTEN;
		goto out;
	}
	res = -EOPNOTSUPP;

out:
	release_sock(sk);

	return res;
}
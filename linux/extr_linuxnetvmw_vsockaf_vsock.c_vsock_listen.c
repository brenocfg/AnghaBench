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
struct vsock_sock {int /*<<< orphan*/  local_addr; } ;
struct socket {scalar_t__ type; scalar_t__ state; struct sock* sk; } ;
struct sock {int sk_max_ack_backlog; int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SS_UNCONNECTED ; 
 int /*<<< orphan*/  TCP_LISTEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  vsock_addr_bound (int /*<<< orphan*/ *) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static int vsock_listen(struct socket *sock, int backlog)
{
	int err;
	struct sock *sk;
	struct vsock_sock *vsk;

	sk = sock->sk;

	lock_sock(sk);

	if (sock->type != SOCK_STREAM) {
		err = -EOPNOTSUPP;
		goto out;
	}

	if (sock->state != SS_UNCONNECTED) {
		err = -EINVAL;
		goto out;
	}

	vsk = vsock_sk(sk);

	if (!vsock_addr_bound(&vsk->local_addr)) {
		err = -EINVAL;
		goto out;
	}

	sk->sk_max_ack_backlog = backlog;
	sk->sk_state = TCP_LISTEN;

	err = 0;

out:
	release_sock(sk);
	return err;
}
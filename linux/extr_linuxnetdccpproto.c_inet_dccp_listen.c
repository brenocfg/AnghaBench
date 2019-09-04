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
struct socket {scalar_t__ state; scalar_t__ type; struct sock* sk; } ;
struct sock {unsigned char sk_state; int sk_max_ack_backlog; } ;

/* Variables and functions */
 int DCCPF_CLOSED ; 
 int DCCPF_LISTEN ; 
 unsigned char DCCP_LISTEN ; 
 int EINVAL ; 
 scalar_t__ SOCK_DCCP ; 
 scalar_t__ SS_UNCONNECTED ; 
 int dccp_listen_start (struct sock*,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

int inet_dccp_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	unsigned char old_state;
	int err;

	lock_sock(sk);

	err = -EINVAL;
	if (sock->state != SS_UNCONNECTED || sock->type != SOCK_DCCP)
		goto out;

	old_state = sk->sk_state;
	if (!((1 << old_state) & (DCCPF_CLOSED | DCCPF_LISTEN)))
		goto out;

	/* Really, if the socket is already in listen state
	 * we can only allow the backlog to be adjusted.
	 */
	if (old_state != DCCP_LISTEN) {
		/*
		 * FIXME: here it probably should be sk->sk_prot->listen_start
		 * see tcp_listen_start
		 */
		err = dccp_listen_start(sk, backlog);
		if (err)
			goto out;
	}
	sk->sk_max_ack_backlog = backlog;
	err = 0;

out:
	release_sock(sk);
	return err;
}
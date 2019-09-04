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
struct socket {int type; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTCONN ; 
 int EPIPE ; 
 int SOCK_SEQPACKET ; 
 int SOCK_STREAM ; 
 scalar_t__ TIPC_DISCONNECTING ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 int /*<<< orphan*/  tipc_sk_connected (struct sock*) ; 

__attribute__((used)) static int tipc_sk_sock_err(struct socket *sock, long *timeout)
{
	struct sock *sk = sock->sk;
	int err = sock_error(sk);
	int typ = sock->type;

	if (err)
		return err;
	if (typ == SOCK_STREAM || typ == SOCK_SEQPACKET) {
		if (sk->sk_state == TIPC_DISCONNECTING)
			return -EPIPE;
		else if (!tipc_sk_connected(sk))
			return -ENOTCONN;
	}
	if (!*timeout)
		return -EAGAIN;
	if (signal_pending(current))
		return sock_intr_errno(*timeout);

	return 0;
}
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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_shutdown; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int SHUT_RDWR ; 
 int /*<<< orphan*/  TIPC_CONN_SHUTDOWN ; 
 scalar_t__ TIPC_DISCONNECTING ; 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __tipc_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  trace_tipc_sk_shutdown (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tipc_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	int res;

	if (how != SHUT_RDWR)
		return -EINVAL;

	lock_sock(sk);

	trace_tipc_sk_shutdown(sk, NULL, TIPC_DUMP_ALL, " ");
	__tipc_shutdown(sock, TIPC_CONN_SHUTDOWN);
	sk->sk_shutdown = SEND_SHUTDOWN;

	if (sk->sk_state == TIPC_DISCONNECTING) {
		/* Discard any unreceived messages */
		__skb_queue_purge(&sk->sk_receive_queue);

		/* Wake up anyone sleeping in poll */
		sk->sk_state_change(sk);
		res = 0;
	} else {
		res = -ENOTCONN;
	}

	release_sock(sk);
	return res;
}
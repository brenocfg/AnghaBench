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
struct TYPE_2__ {int /*<<< orphan*/  deferredq; } ;
struct tipc_sock {int /*<<< orphan*/  rcu; scalar_t__ cong_link_cnt; int /*<<< orphan*/  cong_links; TYPE_1__ mc_method; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_timer; int /*<<< orphan*/  sk_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 int /*<<< orphan*/  TIPC_ERR_NO_PORT ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __tipc_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_stop_timer (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  tipc_dest_list_purge (int /*<<< orphan*/ *) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_callback ; 
 int /*<<< orphan*/  tipc_sk_leave (struct tipc_sock*) ; 
 int /*<<< orphan*/  tipc_sk_remove (struct tipc_sock*) ; 
 int /*<<< orphan*/  tipc_sk_withdraw (struct tipc_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_tipc_sk_release (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tipc_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct tipc_sock *tsk;

	/*
	 * Exit if socket isn't fully initialized (occurs when a failed accept()
	 * releases a pre-allocated child socket that was never used)
	 */
	if (sk == NULL)
		return 0;

	tsk = tipc_sk(sk);
	lock_sock(sk);

	trace_tipc_sk_release(sk, NULL, TIPC_DUMP_ALL, " ");
	__tipc_shutdown(sock, TIPC_ERR_NO_PORT);
	sk->sk_shutdown = SHUTDOWN_MASK;
	tipc_sk_leave(tsk);
	tipc_sk_withdraw(tsk, 0, NULL);
	__skb_queue_purge(&tsk->mc_method.deferredq);
	sk_stop_timer(sk, &sk->sk_timer);
	tipc_sk_remove(tsk);

	sock_orphan(sk);
	/* Reject any messages that accumulated in backlog queue */
	release_sock(sk);
	tipc_dest_list_purge(&tsk->cong_links);
	tsk->cong_link_cnt = 0;
	call_rcu(&tsk->rcu, tipc_sk_callback);
	sock->sk = NULL;

	return 0;
}
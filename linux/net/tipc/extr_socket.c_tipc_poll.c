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
struct tipc_sock {int /*<<< orphan*/  cong_link_cnt; int /*<<< orphan*/  group_is_open; } ;
struct socket {struct sock* sk; } ;
struct sock {int sk_shutdown; int sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDHUP ; 
 int EPOLLRDNORM ; 
 int RCV_SHUTDOWN ; 
 int SHUTDOWN_MASK ; 
#define  TIPC_CONNECTING 132 
#define  TIPC_DISCONNECTING 131 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
#define  TIPC_ESTABLISHED 130 
#define  TIPC_LISTEN 129 
#define  TIPC_OPEN 128 
 int /*<<< orphan*/  skb_queue_empty_lockless (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_poll_wait (struct file*,struct socket*,int /*<<< orphan*/ *) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_type_connectionless (struct sock*) ; 
 int /*<<< orphan*/  trace_tipc_sk_poll (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tsk_conn_cong (struct tipc_sock*) ; 

__attribute__((used)) static __poll_t tipc_poll(struct file *file, struct socket *sock,
			      poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct tipc_sock *tsk = tipc_sk(sk);
	__poll_t revents = 0;

	sock_poll_wait(file, sock, wait);
	trace_tipc_sk_poll(sk, NULL, TIPC_DUMP_ALL, " ");

	if (sk->sk_shutdown & RCV_SHUTDOWN)
		revents |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;
	if (sk->sk_shutdown == SHUTDOWN_MASK)
		revents |= EPOLLHUP;

	switch (sk->sk_state) {
	case TIPC_ESTABLISHED:
		if (!tsk->cong_link_cnt && !tsk_conn_cong(tsk))
			revents |= EPOLLOUT;
		/* fall through */
	case TIPC_LISTEN:
	case TIPC_CONNECTING:
		if (!skb_queue_empty_lockless(&sk->sk_receive_queue))
			revents |= EPOLLIN | EPOLLRDNORM;
		break;
	case TIPC_OPEN:
		if (tsk->group_is_open && !tsk->cong_link_cnt)
			revents |= EPOLLOUT;
		if (!tipc_sk_type_connectionless(sk))
			break;
		if (skb_queue_empty_lockless(&sk->sk_receive_queue))
			break;
		revents |= EPOLLIN | EPOLLRDNORM;
		break;
	case TIPC_DISCONNECTING:
		revents = EPOLLIN | EPOLLRDNORM | EPOLLHUP;
		break;
	}
	return revents;
}
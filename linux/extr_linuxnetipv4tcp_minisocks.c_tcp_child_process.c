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
struct sock {int sk_state; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int TCP_SYN_RECV ; 
 int /*<<< orphan*/  __sk_add_backlog (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_mark_napi_id (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int tcp_rcv_state_process (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_segs_in (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 

int tcp_child_process(struct sock *parent, struct sock *child,
		      struct sk_buff *skb)
{
	int ret = 0;
	int state = child->sk_state;

	/* record NAPI ID of child */
	sk_mark_napi_id(child, skb);

	tcp_segs_in(tcp_sk(child), skb);
	if (!sock_owned_by_user(child)) {
		ret = tcp_rcv_state_process(child, skb);
		/* Wakeup parent, send SIGIO */
		if (state == TCP_SYN_RECV && child->sk_state != state)
			parent->sk_data_ready(parent);
	} else {
		/* Alas, it is possible again, because we do lookup
		 * in main socket hash table and lock on listening
		 * socket does not protect us more.
		 */
		__sk_add_backlog(child, skb);
	}

	bh_unlock_sock(child);
	sock_put(child);
	return ret;
}
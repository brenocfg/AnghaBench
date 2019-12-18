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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_sock {int cong_link_cnt; int /*<<< orphan*/  cong_links; int /*<<< orphan*/  portid; } ;
struct timer_list {int dummy; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_timer; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int ELINKCONG ; 
 int HZ ; 
 scalar_t__ TIPC_CONNECTING ; 
 scalar_t__ TIPC_ESTABLISHED ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct sock* sk ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sk_timer ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  tipc_dest_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tipc_node_xmit (int /*<<< orphan*/ ,struct sk_buff_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_check_probing_state (struct sock*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_sk_retry_connect (struct sock*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tsk_peer_node (struct tipc_sock*) ; 

__attribute__((used)) static void tipc_sk_timeout(struct timer_list *t)
{
	struct sock *sk = from_timer(sk, t, sk_timer);
	struct tipc_sock *tsk = tipc_sk(sk);
	u32 pnode = tsk_peer_node(tsk);
	struct sk_buff_head list;
	int rc = 0;

	__skb_queue_head_init(&list);
	bh_lock_sock(sk);

	/* Try again later if socket is busy */
	if (sock_owned_by_user(sk)) {
		sk_reset_timer(sk, &sk->sk_timer, jiffies + HZ / 20);
		bh_unlock_sock(sk);
		return;
	}

	if (sk->sk_state == TIPC_ESTABLISHED)
		tipc_sk_check_probing_state(sk, &list);
	else if (sk->sk_state == TIPC_CONNECTING)
		tipc_sk_retry_connect(sk, &list);

	bh_unlock_sock(sk);

	if (!skb_queue_empty(&list))
		rc = tipc_node_xmit(sock_net(sk), &list, pnode, tsk->portid);

	/* SYN messages may cause link congestion */
	if (rc == -ELINKCONG) {
		tipc_dest_push(&tsk->cong_links, pnode, 0);
		tsk->cong_link_cnt = 1;
	}
	sock_put(sk);
}
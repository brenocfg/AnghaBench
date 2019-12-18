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
struct tipc_sock {struct tipc_group* group; int /*<<< orphan*/  cong_link_cnt; int /*<<< orphan*/  cong_links; } ;
struct tipc_msg {int dummy; } ;
struct tipc_group {int dummy; } ;
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  sk_rcvbuf; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
#define  CONN_MANAGER 131 
#define  GROUP_PROTOCOL 130 
#define  SOCK_WAKEUP 129 
#define  TOP_SRV 128 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tipc_dest_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_group_member_evt (struct tipc_group*,int*,int /*<<< orphan*/ *,struct tipc_msg*,struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_group_proto_rcv (struct tipc_group*,int*,struct tipc_msg*,struct sk_buff_head*,struct sk_buff_head*) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_conn_proto_rcv (struct tipc_sock*,struct sk_buff*,struct sk_buff_head*,struct sk_buff_head*) ; 

__attribute__((used)) static void tipc_sk_proto_rcv(struct sock *sk,
			      struct sk_buff_head *inputq,
			      struct sk_buff_head *xmitq)
{
	struct sk_buff *skb = __skb_dequeue(inputq);
	struct tipc_sock *tsk = tipc_sk(sk);
	struct tipc_msg *hdr = buf_msg(skb);
	struct tipc_group *grp = tsk->group;
	bool wakeup = false;

	switch (msg_user(hdr)) {
	case CONN_MANAGER:
		tipc_sk_conn_proto_rcv(tsk, skb, inputq, xmitq);
		return;
	case SOCK_WAKEUP:
		tipc_dest_del(&tsk->cong_links, msg_orignode(hdr), 0);
		/* coupled with smp_rmb() in tipc_wait_for_cond() */
		smp_wmb();
		tsk->cong_link_cnt--;
		wakeup = true;
		break;
	case GROUP_PROTOCOL:
		tipc_group_proto_rcv(grp, &wakeup, hdr, inputq, xmitq);
		break;
	case TOP_SRV:
		tipc_group_member_evt(tsk->group, &wakeup, &sk->sk_rcvbuf,
				      hdr, inputq, xmitq);
		break;
	default:
		break;
	}

	if (wakeup)
		sk->sk_write_space(sk);

	kfree_skb(skb);
}
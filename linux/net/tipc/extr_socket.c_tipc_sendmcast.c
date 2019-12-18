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
struct tipc_mc_method {int dummy; } ;
struct tipc_msg {int dummy; } ;
struct tipc_sock {int /*<<< orphan*/  cong_link_cnt; scalar_t__ group; struct tipc_mc_method mc_method; struct tipc_msg phdr; } ;
struct tipc_nlist {int /*<<< orphan*/  remote; int /*<<< orphan*/  local; } ;
struct tipc_name_seq {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; } ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct net {int dummy; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  MCAST_H_SIZE ; 
 int /*<<< orphan*/  TIPC_CLUSTER_SCOPE ; 
 int /*<<< orphan*/  TIPC_DUMP_SK_SNDQ ; 
 int /*<<< orphan*/  TIPC_MCAST_MSG ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_lookup_scope (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_namelower (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_nametype (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_nameupper (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_peek (struct sk_buff_head*) ; 
 struct net* sock_net (struct sock*) ; 
 int tipc_bcast_get_mtu (struct net*) ; 
 int tipc_mcast_xmit (struct net*,struct sk_buff_head*,struct tipc_mc_method*,struct tipc_nlist*,int /*<<< orphan*/ *) ; 
 int tipc_msg_build (struct tipc_msg*,struct msghdr*,int /*<<< orphan*/ ,size_t,int,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_nametbl_lookup_dst_nodes (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_nlist*) ; 
 int /*<<< orphan*/  tipc_nlist_init (struct tipc_nlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nlist_purge (struct tipc_nlist*) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int tipc_wait_for_cond (struct socket*,long*,int) ; 
 int /*<<< orphan*/  trace_tipc_sk_sendmcast (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tipc_sendmcast(struct  socket *sock, struct tipc_name_seq *seq,
			  struct msghdr *msg, size_t dlen, long timeout)
{
	struct sock *sk = sock->sk;
	struct tipc_sock *tsk = tipc_sk(sk);
	struct tipc_msg *hdr = &tsk->phdr;
	struct net *net = sock_net(sk);
	int mtu = tipc_bcast_get_mtu(net);
	struct tipc_mc_method *method = &tsk->mc_method;
	struct sk_buff_head pkts;
	struct tipc_nlist dsts;
	int rc;

	if (tsk->group)
		return -EACCES;

	/* Block or return if any destination link is congested */
	rc = tipc_wait_for_cond(sock, &timeout, !tsk->cong_link_cnt);
	if (unlikely(rc))
		return rc;

	/* Lookup destination nodes */
	tipc_nlist_init(&dsts, tipc_own_addr(net));
	tipc_nametbl_lookup_dst_nodes(net, seq->type, seq->lower,
				      seq->upper, &dsts);
	if (!dsts.local && !dsts.remote)
		return -EHOSTUNREACH;

	/* Build message header */
	msg_set_type(hdr, TIPC_MCAST_MSG);
	msg_set_hdr_sz(hdr, MCAST_H_SIZE);
	msg_set_lookup_scope(hdr, TIPC_CLUSTER_SCOPE);
	msg_set_destport(hdr, 0);
	msg_set_destnode(hdr, 0);
	msg_set_nametype(hdr, seq->type);
	msg_set_namelower(hdr, seq->lower);
	msg_set_nameupper(hdr, seq->upper);

	/* Build message as chain of buffers */
	__skb_queue_head_init(&pkts);
	rc = tipc_msg_build(hdr, msg, 0, dlen, mtu, &pkts);

	/* Send message if build was successful */
	if (unlikely(rc == dlen)) {
		trace_tipc_sk_sendmcast(sk, skb_peek(&pkts),
					TIPC_DUMP_SK_SNDQ, " ");
		rc = tipc_mcast_xmit(net, &pkts, method, &dsts,
				     &tsk->cong_link_cnt);
	}

	tipc_nlist_purge(&dsts);

	return rc ? rc : dlen;
}
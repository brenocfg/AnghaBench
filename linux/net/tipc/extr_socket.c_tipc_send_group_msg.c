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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_msg {int dummy; } ;
struct tipc_mc_method {int rcast; int mandatory; } ;
struct tipc_sock {int /*<<< orphan*/  cong_link_cnt; int /*<<< orphan*/  cong_links; int /*<<< orphan*/  portid; struct tipc_msg phdr; struct tipc_mc_method mc_method; int /*<<< orphan*/  group; } ;
struct tipc_member {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct net {int dummy; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int ELINKCONG ; 
 scalar_t__ GROUP_H_SIZE ; 
 int /*<<< orphan*/  TIPC_GRP_UCAST_MSG ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_grp_bc_seqno (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_dest_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_group_bc_snd_nxt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_group_update_member (struct tipc_member*,int) ; 
 int tipc_msg_build (struct tipc_msg*,struct msghdr*,int /*<<< orphan*/ ,int,int,struct sk_buff_head*) ; 
 int tipc_node_get_mtu (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tipc_node_xmit (struct net*,struct sk_buff_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsk_blocks (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tipc_send_group_msg(struct net *net, struct tipc_sock *tsk,
			       struct msghdr *m, struct tipc_member *mb,
			       u32 dnode, u32 dport, int dlen)
{
	u16 bc_snd_nxt = tipc_group_bc_snd_nxt(tsk->group);
	struct tipc_mc_method *method = &tsk->mc_method;
	int blks = tsk_blocks(GROUP_H_SIZE + dlen);
	struct tipc_msg *hdr = &tsk->phdr;
	struct sk_buff_head pkts;
	int mtu, rc;

	/* Complete message header */
	msg_set_type(hdr, TIPC_GRP_UCAST_MSG);
	msg_set_hdr_sz(hdr, GROUP_H_SIZE);
	msg_set_destport(hdr, dport);
	msg_set_destnode(hdr, dnode);
	msg_set_grp_bc_seqno(hdr, bc_snd_nxt);

	/* Build message as chain of buffers */
	__skb_queue_head_init(&pkts);
	mtu = tipc_node_get_mtu(net, dnode, tsk->portid);
	rc = tipc_msg_build(hdr, m, 0, dlen, mtu, &pkts);
	if (unlikely(rc != dlen))
		return rc;

	/* Send message */
	rc = tipc_node_xmit(net, &pkts, dnode, tsk->portid);
	if (unlikely(rc == -ELINKCONG)) {
		tipc_dest_push(&tsk->cong_links, dnode, 0);
		tsk->cong_link_cnt++;
	}

	/* Update send window */
	tipc_group_update_member(mb, blks);

	/* A broadcast sent within next EXPIRE period must follow same path */
	method->rcast = true;
	method->mandatory = true;
	return dlen;
}
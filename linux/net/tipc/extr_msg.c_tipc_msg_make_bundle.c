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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCAST_PROTOCOL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int INT_H_SIZE ; 
 int /*<<< orphan*/  MSG_BUNDLER ; 
 scalar_t__ MSG_FRAGMENTER ; 
 scalar_t__ TUNNEL_PROTOCOL ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_ack (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_bcast_ack (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_prevnode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_ack (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bcast_ack (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_importance (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_seqno (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 struct sk_buff* tipc_buf_acquire (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_msg_bundle (struct sk_buff*,struct tipc_msg*,int) ; 
 int /*<<< orphan*/  tipc_msg_init (int /*<<< orphan*/ ,struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

bool tipc_msg_make_bundle(struct sk_buff **skb,  struct tipc_msg *msg,
			  u32 mtu, u32 dnode)
{
	struct sk_buff *_skb;
	struct tipc_msg *bmsg;
	u32 msz = msg_size(msg);
	u32 max = mtu - INT_H_SIZE;

	if (msg_user(msg) == MSG_FRAGMENTER)
		return false;
	if (msg_user(msg) == TUNNEL_PROTOCOL)
		return false;
	if (msg_user(msg) == BCAST_PROTOCOL)
		return false;
	if (msz > (max / 2))
		return false;

	_skb = tipc_buf_acquire(max, GFP_ATOMIC);
	if (!_skb)
		return false;

	skb_trim(_skb, INT_H_SIZE);
	bmsg = buf_msg(_skb);
	tipc_msg_init(msg_prevnode(msg), bmsg, MSG_BUNDLER, 0,
		      INT_H_SIZE, dnode);
	msg_set_importance(bmsg, msg_importance(msg));
	msg_set_seqno(bmsg, msg_seqno(msg));
	msg_set_ack(bmsg, msg_ack(msg));
	msg_set_bcast_ack(bmsg, msg_bcast_ack(msg));
	tipc_msg_bundle(_skb, msg, mtu);
	*skb = _skb;
	return true;
}
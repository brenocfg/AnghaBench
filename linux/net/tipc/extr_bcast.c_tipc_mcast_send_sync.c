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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_nlist {int dummy; } ;
struct tipc_msg {int dummy; } ;
struct tipc_mc_method {scalar_t__ rcast; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCAST_H_SIZE ; 
 scalar_t__ MSG_FRAGMENTER ; 
 scalar_t__ TIPC_MCAST_MSG ; 
 int TIPC_MCAST_RBCTL ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 struct tipc_msg* msg_inner_hdr (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_is_rcast (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_is_rcast (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_syn (struct tipc_msg*,int) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_bcast_xmit (struct net*,struct sk_buff_head*,int /*<<< orphan*/ *) ; 
 struct sk_buff* tipc_buf_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_rcast_xmit (struct net*,struct sk_buff_head*,struct tipc_nlist*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tipc_mcast_send_sync(struct net *net, struct sk_buff *skb,
				struct tipc_mc_method *method,
				struct tipc_nlist *dests,
				u16 *cong_link_cnt)
{
	struct tipc_msg *hdr, *_hdr;
	struct sk_buff_head tmpq;
	struct sk_buff *_skb;

	/* Is a cluster supporting with new capabilities ? */
	if (!(tipc_net(net)->capabilities & TIPC_MCAST_RBCTL))
		return 0;

	hdr = buf_msg(skb);
	if (msg_user(hdr) == MSG_FRAGMENTER)
		hdr = msg_inner_hdr(hdr);
	if (msg_type(hdr) != TIPC_MCAST_MSG)
		return 0;

	/* Allocate dummy message */
	_skb = tipc_buf_acquire(MCAST_H_SIZE, GFP_KERNEL);
	if (!_skb)
		return -ENOMEM;

	/* Preparing for 'synching' header */
	msg_set_syn(hdr, 1);

	/* Copy skb's header into a dummy header */
	skb_copy_to_linear_data(_skb, hdr, MCAST_H_SIZE);
	skb_orphan(_skb);

	/* Reverse method for dummy message */
	_hdr = buf_msg(_skb);
	msg_set_size(_hdr, MCAST_H_SIZE);
	msg_set_is_rcast(_hdr, !msg_is_rcast(hdr));

	__skb_queue_head_init(&tmpq);
	__skb_queue_tail(&tmpq, _skb);
	if (method->rcast)
		tipc_bcast_xmit(net, &tmpq, cong_link_cnt);
	else
		tipc_rcast_xmit(net, &tmpq, dests, cong_link_cnt);

	/* This queue should normally be empty by now */
	__skb_queue_purge(&tmpq);

	return 0;
}
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
struct tipc_msg {int dummy; } ;
struct tipc_link {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct sk_buff_head inputq; } ;

/* Variables and functions */
 scalar_t__ BCAST_PROTOCOL ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ msg_mc_netid (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 TYPE_1__* tipc_bc_base (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_xmit (struct net*,struct sk_buff_head*) ; 
 int tipc_link_bc_nack_rcv (struct tipc_link*,struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct tipc_link*) ; 
 int tipc_link_rcv (struct tipc_link*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ tipc_netid (struct net*) ; 
 int /*<<< orphan*/  tipc_sk_rcv (struct net*,struct sk_buff_head*) ; 

int tipc_bcast_rcv(struct net *net, struct tipc_link *l, struct sk_buff *skb)
{
	struct tipc_msg *hdr = buf_msg(skb);
	struct sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	struct sk_buff_head xmitq;
	int rc;

	__skb_queue_head_init(&xmitq);

	if (msg_mc_netid(hdr) != tipc_netid(net) || !tipc_link_is_up(l)) {
		kfree_skb(skb);
		return 0;
	}

	tipc_bcast_lock(net);
	if (msg_user(hdr) == BCAST_PROTOCOL)
		rc = tipc_link_bc_nack_rcv(l, skb, &xmitq);
	else
		rc = tipc_link_rcv(l, skb, NULL);
	tipc_bcast_unlock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	if (!skb_queue_empty(inputq))
		tipc_sk_rcv(net, inputq);

	return rc;
}
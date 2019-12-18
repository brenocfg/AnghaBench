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
struct net {int dummy; } ;
struct TYPE_2__ {struct sk_buff_head inputq; } ;

/* Variables and functions */
 scalar_t__ STATE_MSG ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  msg_bc_ack_invalid (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_bcast_ack (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 TYPE_1__* tipc_bc_base (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_xmit (struct net*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_bc_ack_rcv (struct tipc_link*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_bc_init_rcv (struct tipc_link*,struct tipc_msg*) ; 
 int tipc_link_bc_sync_rcv (struct tipc_link*,struct tipc_msg*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_sk_rcv (struct net*,struct sk_buff_head*) ; 

int tipc_bcast_sync_rcv(struct net *net, struct tipc_link *l,
			struct tipc_msg *hdr)
{
	struct sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	struct sk_buff_head xmitq;
	int rc = 0;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_lock(net);
	if (msg_type(hdr) != STATE_MSG) {
		tipc_link_bc_init_rcv(l, hdr);
	} else if (!msg_bc_ack_invalid(hdr)) {
		tipc_link_bc_ack_rcv(l, msg_bcast_ack(hdr), &xmitq);
		rc = tipc_link_bc_sync_rcv(l, hdr, &xmitq);
	}
	tipc_bcast_unlock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	if (!skb_queue_empty(inputq))
		tipc_sk_rcv(net, inputq);
	return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  link_congs; } ;
struct tipc_link {TYPE_1__ stats; int /*<<< orphan*/  wakeupq; int /*<<< orphan*/  addr; int /*<<< orphan*/  net; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  chain_imp; } ;

/* Variables and functions */
 int ELINKCONG ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  INT_H_SIZE ; 
 int /*<<< orphan*/  SOCK_WAKEUP ; 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 TYPE_2__* TIPC_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_dest_droppable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* tipc_msg_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_link_conges (struct tipc_link*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int link_schedule_user(struct tipc_link *l, struct tipc_msg *hdr)
{
	u32 dnode = tipc_own_addr(l->net);
	u32 dport = msg_origport(hdr);
	struct sk_buff *skb;

	/* Create and schedule wakeup pseudo message */
	skb = tipc_msg_create(SOCK_WAKEUP, 0, INT_H_SIZE, 0,
			      dnode, l->addr, dport, 0, 0);
	if (!skb)
		return -ENOBUFS;
	msg_set_dest_droppable(buf_msg(skb), true);
	TIPC_SKB_CB(skb)->chain_imp = msg_importance(hdr);
	skb_queue_tail(&l->wakeupq, skb);
	l->stats.link_congs++;
	trace_tipc_link_conges(l, TIPC_DUMP_ALL, "wakeup scheduled!");
	return -ELINKCONG;
}
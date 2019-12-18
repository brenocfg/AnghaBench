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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  usr_handle; } ;
struct tipc_event {TYPE_1__ s; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_H_SIZE ; 
 int /*<<< orphan*/  TOP_SRV ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct tipc_event*,int) ; 
 int /*<<< orphan*/  msg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_dest_droppable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_loopback_trace (struct net*,struct sk_buff_head*) ; 
 struct sk_buff* tipc_msg_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 
 int /*<<< orphan*/  tipc_sk_rcv (struct net*,struct sk_buff_head*) ; 

__attribute__((used)) static void tipc_topsrv_kern_evt(struct net *net, struct tipc_event *evt)
{
	u32 port = *(u32 *)&evt->s.usr_handle;
	u32 self = tipc_own_addr(net);
	struct sk_buff_head evtq;
	struct sk_buff *skb;

	skb = tipc_msg_create(TOP_SRV, 0, INT_H_SIZE, sizeof(*evt),
			      self, self, port, port, 0);
	if (!skb)
		return;
	msg_set_dest_droppable(buf_msg(skb), true);
	memcpy(msg_data(buf_msg(skb)), evt, sizeof(*evt));
	skb_queue_head_init(&evtq);
	__skb_queue_tail(&evtq, skb);
	tipc_loopback_trace(net, &evtq);
	tipc_sk_rcv(net, &evtq);
}
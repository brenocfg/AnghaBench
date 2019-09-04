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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_destnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_origport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_xmit_skb (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tipc_node_distr_xmit(struct net *net, struct sk_buff_head *xmitq)
{
	struct sk_buff *skb;
	u32 selector, dnode;

	while ((skb = __skb_dequeue(xmitq))) {
		selector = msg_origport(buf_msg(skb));
		dnode = msg_destnode(buf_msg(skb));
		tipc_node_xmit_skb(net, skb, dnode, selector);
	}
	return 0;
}
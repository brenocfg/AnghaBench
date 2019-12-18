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
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_node_xmit (struct net*,struct sk_buff_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tipc_node_xmit_skb(struct net *net, struct sk_buff *skb, u32 dnode,
		       u32 selector)
{
	struct sk_buff_head head;

	__skb_queue_head_init(&head);
	__skb_queue_tail(&head, skb);
	tipc_node_xmit(net, &head, dnode, selector);
	return 0;
}
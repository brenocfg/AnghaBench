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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 scalar_t__ tipc_msg_reverse (int /*<<< orphan*/ ,struct sk_buff**,int) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 

void tipc_skb_reject(struct net *net, int err, struct sk_buff *skb,
		     struct sk_buff_head *xmitq)
{
	if (tipc_msg_reverse(tipc_own_addr(net), &skb, err))
		__skb_queue_tail(xmitq, skb);
}
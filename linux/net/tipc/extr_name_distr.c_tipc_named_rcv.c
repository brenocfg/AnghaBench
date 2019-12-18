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
typedef  int uint ;
typedef  int /*<<< orphan*/  u32 ;
struct tipc_net {int /*<<< orphan*/  nametbl_lock; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct distr_item {int dummy; } ;

/* Variables and functions */
 int ITEM_SIZE ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ msg_data (struct tipc_msg*) ; 
 int msg_data_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int msg_type (struct tipc_msg*) ; 
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_id ; 
 int /*<<< orphan*/  tipc_update_nametbl (struct net*,struct distr_item*,int /*<<< orphan*/ ,int) ; 

void tipc_named_rcv(struct net *net, struct sk_buff_head *inputq)
{
	struct tipc_net *tn = net_generic(net, tipc_net_id);
	struct tipc_msg *msg;
	struct distr_item *item;
	uint count;
	u32 node;
	struct sk_buff *skb;
	int mtype;

	spin_lock_bh(&tn->nametbl_lock);
	for (skb = skb_dequeue(inputq); skb; skb = skb_dequeue(inputq)) {
		skb_linearize(skb);
		msg = buf_msg(skb);
		mtype = msg_type(msg);
		item = (struct distr_item *)msg_data(msg);
		count = msg_data_sz(msg) / ITEM_SIZE;
		node = msg_orignode(msg);
		while (count--) {
			tipc_update_nametbl(net, item, node, mtype);
			item++;
		}
		kfree_skb(skb);
	}
	spin_unlock_bh(&tn->nametbl_lock);
}
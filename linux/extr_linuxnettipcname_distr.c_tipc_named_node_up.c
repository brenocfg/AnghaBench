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
struct net {int dummy; } ;
struct name_table {int /*<<< orphan*/  cluster_scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  named_distribute (struct net*,struct sk_buff_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct name_table* tipc_name_table (struct net*) ; 
 int /*<<< orphan*/  tipc_node_xmit (struct net*,struct sk_buff_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tipc_named_node_up(struct net *net, u32 dnode)
{
	struct name_table *nt = tipc_name_table(net);
	struct sk_buff_head head;

	__skb_queue_head_init(&head);

	rcu_read_lock();
	named_distribute(net, &head, dnode, &nt->cluster_scope);
	rcu_read_unlock();

	tipc_node_xmit(net, &head, dnode, 0);
}
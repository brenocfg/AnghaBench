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
struct tipc_net {int /*<<< orphan*/  nametbl_lock; } ;
struct sk_buff {int dummy; } ;
struct publication {int /*<<< orphan*/  binding_sock; } ;
struct net {int dummy; } ;
struct name_table {int /*<<< orphan*/  local_publ_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct publication*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct name_table* tipc_name_table (struct net*) ; 
 struct sk_buff* tipc_named_withdraw (struct net*,struct publication*) ; 
 struct publication* tipc_nametbl_remove_publ (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_node_broadcast (struct net*,struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 

int tipc_nametbl_withdraw(struct net *net, u32 type, u32 lower,
			  u32 upper, u32 key)
{
	struct name_table *nt = tipc_name_table(net);
	struct tipc_net *tn = tipc_net(net);
	u32 self = tipc_own_addr(net);
	struct sk_buff *skb = NULL;
	struct publication *p;

	spin_lock_bh(&tn->nametbl_lock);

	p = tipc_nametbl_remove_publ(net, type, lower, upper, self, key);
	if (p) {
		nt->local_publ_count--;
		skb = tipc_named_withdraw(net, p);
		list_del_init(&p->binding_sock);
		kfree_rcu(p, rcu);
	} else {
		pr_err("Failed to remove local publication {%u,%u,%u}/%u\n",
		       type, lower, upper, key);
	}
	spin_unlock_bh(&tn->nametbl_lock);

	if (skb) {
		tipc_node_broadcast(net, skb);
		return 1;
	}
	return 0;
}
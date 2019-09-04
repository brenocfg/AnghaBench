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
struct sk_buff {int dummy; } ;
struct publication {scalar_t__ scope; int /*<<< orphan*/  binding_node; } ;
struct net {int dummy; } ;
struct name_table {int /*<<< orphan*/  cluster_scope; int /*<<< orphan*/  node_scope; } ;
struct distr_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_SIZE ; 
 int /*<<< orphan*/  PUBLICATION ; 
 scalar_t__ TIPC_NODE_SCOPE ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ msg_data (int /*<<< orphan*/ ) ; 
 struct sk_buff* named_prepare_buf (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  publ_to_item (struct distr_item*,struct publication*) ; 
 struct name_table* tipc_name_table (struct net*) ; 

struct sk_buff *tipc_named_publish(struct net *net, struct publication *publ)
{
	struct name_table *nt = tipc_name_table(net);
	struct distr_item *item;
	struct sk_buff *skb;

	if (publ->scope == TIPC_NODE_SCOPE) {
		list_add_tail_rcu(&publ->binding_node, &nt->node_scope);
		return NULL;
	}
	list_add_tail_rcu(&publ->binding_node, &nt->cluster_scope);

	skb = named_prepare_buf(net, PUBLICATION, ITEM_SIZE, 0);
	if (!skb) {
		pr_warn("Publication distribution failure\n");
		return NULL;
	}

	item = (struct distr_item *)msg_data(buf_msg(skb));
	publ_to_item(item, publ);
	return skb;
}
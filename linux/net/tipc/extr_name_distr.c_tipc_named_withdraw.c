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
struct name_table {int /*<<< orphan*/  cluster_scope_lock; } ;
struct distr_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_SIZE ; 
 scalar_t__ TIPC_NODE_SCOPE ; 
 int /*<<< orphan*/  WITHDRAWAL ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ msg_data (int /*<<< orphan*/ ) ; 
 struct sk_buff* named_prepare_buf (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  publ_to_item (struct distr_item*,struct publication*) ; 
 struct name_table* tipc_name_table (struct net*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct sk_buff *tipc_named_withdraw(struct net *net, struct publication *publ)
{
	struct name_table *nt = tipc_name_table(net);
	struct sk_buff *buf;
	struct distr_item *item;

	write_lock_bh(&nt->cluster_scope_lock);
	list_del(&publ->binding_node);
	write_unlock_bh(&nt->cluster_scope_lock);
	if (publ->scope == TIPC_NODE_SCOPE)
		return NULL;

	buf = named_prepare_buf(net, WITHDRAWAL, ITEM_SIZE, 0);
	if (!buf) {
		pr_warn("Withdrawal distribution failure\n");
		return NULL;
	}

	item = (struct distr_item *)msg_data(buf_msg(buf));
	publ_to_item(item, publ);
	return buf;
}
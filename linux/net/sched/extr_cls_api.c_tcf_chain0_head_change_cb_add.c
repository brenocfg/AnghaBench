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
struct tcf_proto {int dummy; } ;
struct tcf_filter_chain_list_item {int /*<<< orphan*/  list; int /*<<< orphan*/  chain_head_change_priv; int /*<<< orphan*/  chain_head_change; } ;
struct tcf_chain {int /*<<< orphan*/  filter_chain_lock; int /*<<< orphan*/  filter_chain; } ;
struct tcf_block_ext_info {int /*<<< orphan*/  chain_head_change_priv; int /*<<< orphan*/  chain_head_change; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter_chain_list; struct tcf_chain* chain; } ;
struct tcf_block {int /*<<< orphan*/  lock; TYPE_1__ chain0; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 struct tcf_filter_chain_list_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tcf_proto* tcf_chain_dereference (int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_head_change_item (struct tcf_filter_chain_list_item*,struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_chain_hold (struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 

__attribute__((used)) static int
tcf_chain0_head_change_cb_add(struct tcf_block *block,
			      struct tcf_block_ext_info *ei,
			      struct netlink_ext_ack *extack)
{
	struct tcf_filter_chain_list_item *item;
	struct tcf_chain *chain0;

	item = kmalloc(sizeof(*item), GFP_KERNEL);
	if (!item) {
		NL_SET_ERR_MSG(extack, "Memory allocation for head change callback item failed");
		return -ENOMEM;
	}
	item->chain_head_change = ei->chain_head_change;
	item->chain_head_change_priv = ei->chain_head_change_priv;

	mutex_lock(&block->lock);
	chain0 = block->chain0.chain;
	if (chain0)
		tcf_chain_hold(chain0);
	else
		list_add(&item->list, &block->chain0.filter_chain_list);
	mutex_unlock(&block->lock);

	if (chain0) {
		struct tcf_proto *tp_head;

		mutex_lock(&chain0->filter_chain_lock);

		tp_head = tcf_chain_dereference(chain0->filter_chain, chain0);
		if (tp_head)
			tcf_chain_head_change_item(item, tp_head);

		mutex_lock(&block->lock);
		list_add(&item->list, &block->chain0.filter_chain_list);
		mutex_unlock(&block->lock);

		mutex_unlock(&chain0->filter_chain_lock);
		tcf_chain_put(chain0);
	}

	return 0;
}
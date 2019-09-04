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
struct tcf_filter_chain_list_item {int /*<<< orphan*/  list; int /*<<< orphan*/  chain_head_change_priv; int /*<<< orphan*/  chain_head_change; } ;
struct tcf_chain {scalar_t__ filter_chain; } ;
struct tcf_block_ext_info {int /*<<< orphan*/  chain_head_change_priv; int /*<<< orphan*/  chain_head_change; } ;
struct TYPE_2__ {int /*<<< orphan*/  filter_chain_list; struct tcf_chain* chain; } ;
struct tcf_block {TYPE_1__ chain0; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 struct tcf_filter_chain_list_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_chain_head_change_item (struct tcf_filter_chain_list_item*,scalar_t__) ; 

__attribute__((used)) static int
tcf_chain0_head_change_cb_add(struct tcf_block *block,
			      struct tcf_block_ext_info *ei,
			      struct netlink_ext_ack *extack)
{
	struct tcf_chain *chain0 = block->chain0.chain;
	struct tcf_filter_chain_list_item *item;

	item = kmalloc(sizeof(*item), GFP_KERNEL);
	if (!item) {
		NL_SET_ERR_MSG(extack, "Memory allocation for head change callback item failed");
		return -ENOMEM;
	}
	item->chain_head_change = ei->chain_head_change;
	item->chain_head_change_priv = ei->chain_head_change_priv;
	if (chain0 && chain0->filter_chain)
		tcf_chain_head_change_item(item, chain0->filter_chain);
	list_add(&item->list, &block->chain0.filter_chain_list);
	return 0;
}
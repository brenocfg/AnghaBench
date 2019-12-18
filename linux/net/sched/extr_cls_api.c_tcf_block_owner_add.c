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
struct tcf_block_owner_item {int binder_type; int /*<<< orphan*/  list; struct Qdisc* q; } ;
struct tcf_block {int /*<<< orphan*/  owner_list; } ;
struct Qdisc {int dummy; } ;
typedef  enum flow_block_binder_type { ____Placeholder_flow_block_binder_type } flow_block_binder_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tcf_block_owner_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcf_block_owner_add(struct tcf_block *block,
			       struct Qdisc *q,
			       enum flow_block_binder_type binder_type)
{
	struct tcf_block_owner_item *item;

	item = kmalloc(sizeof(*item), GFP_KERNEL);
	if (!item)
		return -ENOMEM;
	item->q = q;
	item->binder_type = binder_type;
	list_add(&item->list, &block->owner_list);
	return 0;
}
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
struct sw_flow_mask {int /*<<< orphan*/  ref_count; int /*<<< orphan*/  list; int /*<<< orphan*/  range; int /*<<< orphan*/  key; } ;
struct sw_flow {struct sw_flow_mask* mask; } ;
struct flow_table {int /*<<< orphan*/  mask_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct sw_flow_mask* flow_mask_find (struct flow_table*,struct sw_flow_mask const*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sw_flow_mask* mask_alloc () ; 

__attribute__((used)) static int flow_mask_insert(struct flow_table *tbl, struct sw_flow *flow,
			    const struct sw_flow_mask *new)
{
	struct sw_flow_mask *mask;
	mask = flow_mask_find(tbl, new);
	if (!mask) {
		/* Allocate a new mask if none exsits. */
		mask = mask_alloc();
		if (!mask)
			return -ENOMEM;
		mask->key = new->key;
		mask->range = new->range;
		list_add_rcu(&mask->list, &tbl->mask_list);
	} else {
		BUG_ON(!mask->ref_count);
		mask->ref_count++;
	}

	flow->mask = mask;
	return 0;
}
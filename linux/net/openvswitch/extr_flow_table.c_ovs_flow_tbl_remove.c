#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct table_instance {size_t node_ver; } ;
struct TYPE_4__ {int /*<<< orphan*/ * node; } ;
struct TYPE_3__ {int /*<<< orphan*/ * node; } ;
struct sw_flow {int /*<<< orphan*/  mask; TYPE_2__ ufid_table; int /*<<< orphan*/  id; TYPE_1__ flow_table; } ;
struct flow_table {scalar_t__ count; int /*<<< orphan*/  ufid_count; int /*<<< orphan*/  ufid_ti; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  flow_mask_remove (struct flow_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ ovs_identifier_is_ufid (int /*<<< orphan*/ *) ; 
 struct table_instance* ovsl_dereference (int /*<<< orphan*/ ) ; 

void ovs_flow_tbl_remove(struct flow_table *table, struct sw_flow *flow)
{
	struct table_instance *ti = ovsl_dereference(table->ti);
	struct table_instance *ufid_ti = ovsl_dereference(table->ufid_ti);

	BUG_ON(table->count == 0);
	hlist_del_rcu(&flow->flow_table.node[ti->node_ver]);
	table->count--;
	if (ovs_identifier_is_ufid(&flow->id)) {
		hlist_del_rcu(&flow->ufid_table.node[ufid_ti->node_ver]);
		table->ufid_count--;
	}

	/* RCU delete the mask. 'flow->mask' is not NULLed, as it should be
	 * accessible as long as the RCU read lock is held.
	 */
	flow_mask_remove(table, flow->mask);
}
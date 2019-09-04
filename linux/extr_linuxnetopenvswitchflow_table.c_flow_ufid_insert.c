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
struct table_instance {scalar_t__ n_buckets; int /*<<< orphan*/  rcu; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct sw_flow {int /*<<< orphan*/  id; TYPE_1__ ufid_table; } ;
struct flow_table {scalar_t__ ufid_count; int /*<<< orphan*/  ufid_ti; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_tbl_destroy_rcu_cb ; 
 struct table_instance* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct table_instance*) ; 
 struct table_instance* table_instance_expand (struct table_instance*,int) ; 
 int /*<<< orphan*/  ufid_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufid_table_instance_insert (struct table_instance*,struct sw_flow*) ; 

__attribute__((used)) static void flow_ufid_insert(struct flow_table *table, struct sw_flow *flow)
{
	struct table_instance *ti;

	flow->ufid_table.hash = ufid_hash(&flow->id);
	ti = ovsl_dereference(table->ufid_ti);
	ufid_table_instance_insert(ti, flow);
	table->ufid_count++;

	/* Expand table, if necessary, to make room. */
	if (table->ufid_count > ti->n_buckets) {
		struct table_instance *new_ti;

		new_ti = table_instance_expand(ti, true);
		if (new_ti) {
			rcu_assign_pointer(table->ufid_ti, new_ti);
			call_rcu(&ti->rcu, flow_tbl_destroy_rcu_cb);
		}
	}
}
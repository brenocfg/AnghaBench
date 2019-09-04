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
struct table_instance {int dummy; } ;
struct flow_table {scalar_t__ ufid_count; scalar_t__ count; int /*<<< orphan*/  last_rehash; int /*<<< orphan*/  ufid_ti; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TBL_MIN_BUCKETS ; 
 int /*<<< orphan*/  __table_instance_destroy (struct table_instance*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct table_instance* ovsl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct table_instance*) ; 
 struct table_instance* table_instance_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_instance_destroy (struct table_instance*,struct table_instance*,int) ; 

int ovs_flow_tbl_flush(struct flow_table *flow_table)
{
	struct table_instance *old_ti, *new_ti;
	struct table_instance *old_ufid_ti, *new_ufid_ti;

	new_ti = table_instance_alloc(TBL_MIN_BUCKETS);
	if (!new_ti)
		return -ENOMEM;
	new_ufid_ti = table_instance_alloc(TBL_MIN_BUCKETS);
	if (!new_ufid_ti)
		goto err_free_ti;

	old_ti = ovsl_dereference(flow_table->ti);
	old_ufid_ti = ovsl_dereference(flow_table->ufid_ti);

	rcu_assign_pointer(flow_table->ti, new_ti);
	rcu_assign_pointer(flow_table->ufid_ti, new_ufid_ti);
	flow_table->last_rehash = jiffies;
	flow_table->count = 0;
	flow_table->ufid_count = 0;

	table_instance_destroy(old_ti, old_ufid_ti, true);
	return 0;

err_free_ti:
	__table_instance_destroy(new_ti);
	return -ENOMEM;
}
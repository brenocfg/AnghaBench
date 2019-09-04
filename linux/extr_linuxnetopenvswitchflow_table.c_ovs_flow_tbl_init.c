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
struct flow_table {scalar_t__ ufid_count; scalar_t__ count; int /*<<< orphan*/  last_rehash; int /*<<< orphan*/  mask_list; int /*<<< orphan*/  ufid_ti; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TBL_MIN_BUCKETS ; 
 int /*<<< orphan*/  __table_instance_destroy (struct table_instance*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct table_instance*) ; 
 struct table_instance* table_instance_alloc (int /*<<< orphan*/ ) ; 

int ovs_flow_tbl_init(struct flow_table *table)
{
	struct table_instance *ti, *ufid_ti;

	ti = table_instance_alloc(TBL_MIN_BUCKETS);

	if (!ti)
		return -ENOMEM;

	ufid_ti = table_instance_alloc(TBL_MIN_BUCKETS);
	if (!ufid_ti)
		goto free_ti;

	rcu_assign_pointer(table->ti, ti);
	rcu_assign_pointer(table->ufid_ti, ufid_ti);
	INIT_LIST_HEAD(&table->mask_list);
	table->last_rehash = jiffies;
	table->count = 0;
	table->ufid_count = 0;
	return 0;

free_ti:
	__table_instance_destroy(ti);
	return -ENOMEM;
}
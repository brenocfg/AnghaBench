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
struct nf_flowtable {int /*<<< orphan*/  rhashtable; int /*<<< orphan*/  gc_work; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flowtable_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_flow_offload_gc_step ; 
 int /*<<< orphan*/  nf_flow_table_do_cleanup ; 
 int /*<<< orphan*/  nf_flow_table_iterate (struct nf_flowtable*,int /*<<< orphan*/ ,struct nf_flowtable*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void nf_flow_table_free(struct nf_flowtable *flow_table)
{
	mutex_lock(&flowtable_lock);
	list_del(&flow_table->list);
	mutex_unlock(&flowtable_lock);
	cancel_delayed_work_sync(&flow_table->gc_work);
	nf_flow_table_iterate(flow_table, nf_flow_table_do_cleanup, NULL);
	nf_flow_table_iterate(flow_table, nf_flow_offload_gc_step, flow_table);
	rhashtable_destroy(&flow_table->rhashtable);
}
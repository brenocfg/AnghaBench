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
struct nf_flowtable {int /*<<< orphan*/  list; int /*<<< orphan*/  gc_work; int /*<<< orphan*/  rhashtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowtable_lock ; 
 int /*<<< orphan*/  flowtables ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_flow_offload_rhash_params ; 
 int /*<<< orphan*/  nf_flow_offload_work_gc ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

int nf_flow_table_init(struct nf_flowtable *flowtable)
{
	int err;

	INIT_DEFERRABLE_WORK(&flowtable->gc_work, nf_flow_offload_work_gc);

	err = rhashtable_init(&flowtable->rhashtable,
			      &nf_flow_offload_rhash_params);
	if (err < 0)
		return err;

	queue_delayed_work(system_power_efficient_wq,
			   &flowtable->gc_work, HZ);

	mutex_lock(&flowtable_lock);
	list_add(&flowtable->list, &flowtables);
	mutex_unlock(&flowtable_lock);

	return 0;
}
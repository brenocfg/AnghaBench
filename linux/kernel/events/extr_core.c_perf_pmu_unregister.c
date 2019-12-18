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
struct pmu {scalar_t__ type; int /*<<< orphan*/  dev; scalar_t__ nr_addr_filters; int /*<<< orphan*/  pmu_disable_count; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_MAX ; 
 int /*<<< orphan*/  dev_attr_nr_addr_filters ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pmu_context (struct pmu*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pmu_bus_running ; 
 int /*<<< orphan*/  pmu_idr ; 
 int /*<<< orphan*/  pmus_lock ; 
 int /*<<< orphan*/  pmus_srcu ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void perf_pmu_unregister(struct pmu *pmu)
{
	mutex_lock(&pmus_lock);
	list_del_rcu(&pmu->entry);

	/*
	 * We dereference the pmu list under both SRCU and regular RCU, so
	 * synchronize against both of those.
	 */
	synchronize_srcu(&pmus_srcu);
	synchronize_rcu();

	free_percpu(pmu->pmu_disable_count);
	if (pmu->type >= PERF_TYPE_MAX)
		idr_remove(&pmu_idr, pmu->type);
	if (pmu_bus_running) {
		if (pmu->nr_addr_filters)
			device_remove_file(pmu->dev, &dev_attr_nr_addr_filters);
		device_del(pmu->dev);
		put_device(pmu->dev);
	}
	free_pmu_context(pmu);
	mutex_unlock(&pmus_lock);
}
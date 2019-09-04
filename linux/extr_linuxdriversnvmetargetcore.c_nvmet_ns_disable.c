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
struct nvmet_subsys {scalar_t__ max_nsid; int /*<<< orphan*/  lock; int /*<<< orphan*/  nr_namespaces; } ;
struct nvmet_ns {int enabled; scalar_t__ nsid; int /*<<< orphan*/  ref; int /*<<< orphan*/  disable_done; int /*<<< orphan*/  dev_link; struct nvmet_subsys* subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nvmet_max_nsid (struct nvmet_subsys*) ; 
 int /*<<< orphan*/  nvmet_ns_changed (struct nvmet_subsys*,scalar_t__) ; 
 int /*<<< orphan*/  nvmet_ns_dev_disable (struct nvmet_ns*) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void nvmet_ns_disable(struct nvmet_ns *ns)
{
	struct nvmet_subsys *subsys = ns->subsys;

	mutex_lock(&subsys->lock);
	if (!ns->enabled)
		goto out_unlock;

	ns->enabled = false;
	list_del_rcu(&ns->dev_link);
	if (ns->nsid == subsys->max_nsid)
		subsys->max_nsid = nvmet_max_nsid(subsys);
	mutex_unlock(&subsys->lock);

	/*
	 * Now that we removed the namespaces from the lookup list, we
	 * can kill the per_cpu ref and wait for any remaining references
	 * to be dropped, as well as a RCU grace period for anyone only
	 * using the namepace under rcu_read_lock().  Note that we can't
	 * use call_rcu here as we need to ensure the namespaces have
	 * been fully destroyed before unloading the module.
	 */
	percpu_ref_kill(&ns->ref);
	synchronize_rcu();
	wait_for_completion(&ns->disable_done);
	percpu_ref_exit(&ns->ref);

	mutex_lock(&subsys->lock);
	subsys->nr_namespaces--;
	nvmet_ns_changed(subsys, ns->nsid);
	nvmet_ns_dev_disable(ns);
out_unlock:
	mutex_unlock(&subsys->lock);
}
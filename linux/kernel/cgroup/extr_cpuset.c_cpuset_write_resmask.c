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
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;
struct cpuset {int /*<<< orphan*/  css; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
#define  FILE_CPULIST 129 
#define  FILE_MEMLIST 128 
 struct cpuset* alloc_trial_cpuset (struct cpuset*) ; 
 int /*<<< orphan*/  cpuset_hotplug_work ; 
 int /*<<< orphan*/  cpuset_migrate_mm_wq ; 
 int /*<<< orphan*/  cpuset_rwsem ; 
 struct cpuset* css_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpuset (struct cpuset*) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  is_cpuset_online (struct cpuset*) ; 
 int /*<<< orphan*/  kernfs_break_active_protection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_unbreak_active_protection (int /*<<< orphan*/ ) ; 
 TYPE_1__* of_cft (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 char* strstrip (char*) ; 
 int update_cpumask (struct cpuset*,struct cpuset*,char*) ; 
 int update_nodemask (struct cpuset*,struct cpuset*,char*) ; 

__attribute__((used)) static ssize_t cpuset_write_resmask(struct kernfs_open_file *of,
				    char *buf, size_t nbytes, loff_t off)
{
	struct cpuset *cs = css_cs(of_css(of));
	struct cpuset *trialcs;
	int retval = -ENODEV;

	buf = strstrip(buf);

	/*
	 * CPU or memory hotunplug may leave @cs w/o any execution
	 * resources, in which case the hotplug code asynchronously updates
	 * configuration and transfers all tasks to the nearest ancestor
	 * which can execute.
	 *
	 * As writes to "cpus" or "mems" may restore @cs's execution
	 * resources, wait for the previously scheduled operations before
	 * proceeding, so that we don't end up keep removing tasks added
	 * after execution capability is restored.
	 *
	 * cpuset_hotplug_work calls back into cgroup core via
	 * cgroup_transfer_tasks() and waiting for it from a cgroupfs
	 * operation like this one can lead to a deadlock through kernfs
	 * active_ref protection.  Let's break the protection.  Losing the
	 * protection is okay as we check whether @cs is online after
	 * grabbing cpuset_mutex anyway.  This only happens on the legacy
	 * hierarchies.
	 */
	css_get(&cs->css);
	kernfs_break_active_protection(of->kn);
	flush_work(&cpuset_hotplug_work);

	get_online_cpus();
	percpu_down_write(&cpuset_rwsem);
	if (!is_cpuset_online(cs))
		goto out_unlock;

	trialcs = alloc_trial_cpuset(cs);
	if (!trialcs) {
		retval = -ENOMEM;
		goto out_unlock;
	}

	switch (of_cft(of)->private) {
	case FILE_CPULIST:
		retval = update_cpumask(cs, trialcs, buf);
		break;
	case FILE_MEMLIST:
		retval = update_nodemask(cs, trialcs, buf);
		break;
	default:
		retval = -EINVAL;
		break;
	}

	free_cpuset(trialcs);
out_unlock:
	percpu_up_write(&cpuset_rwsem);
	put_online_cpus();
	kernfs_unbreak_active_protection(of->kn);
	css_put(&cs->css);
	flush_workqueue(cpuset_migrate_mm_wq);
	return retval ?: nbytes;
}
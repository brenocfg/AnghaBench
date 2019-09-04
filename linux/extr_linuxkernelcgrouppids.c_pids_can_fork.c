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
struct task_struct {int dummy; } ;
struct pids_cgroup {int /*<<< orphan*/  events_file; int /*<<< orphan*/  events_limit; } ;
struct cgroup_subsys_state {int /*<<< orphan*/  cgroup; } ;

/* Variables and functions */
 int atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_file_notify (int /*<<< orphan*/ *) ; 
 struct pids_cgroup* css_pids (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pids_cgrp_id ; 
 int pids_try_charge (struct pids_cgroup*,int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_cont_cgroup_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct cgroup_subsys_state* task_css_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pids_can_fork(struct task_struct *task)
{
	struct cgroup_subsys_state *css;
	struct pids_cgroup *pids;
	int err;

	css = task_css_check(current, pids_cgrp_id, true);
	pids = css_pids(css);
	err = pids_try_charge(pids, 1);
	if (err) {
		/* Only log the first time events_limit is incremented. */
		if (atomic64_inc_return(&pids->events_limit) == 1) {
			pr_info("cgroup: fork rejected by pids controller in ");
			pr_cont_cgroup_path(css->cgroup);
			pr_cont("\n");
		}
		cgroup_file_notify(&pids->events_file);
	}
	return err;
}
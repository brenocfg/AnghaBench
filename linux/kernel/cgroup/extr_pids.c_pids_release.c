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
struct pids_cgroup {int dummy; } ;

/* Variables and functions */
 struct pids_cgroup* css_pids (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pids_cgrp_id ; 
 int /*<<< orphan*/  pids_uncharge (struct pids_cgroup*,int) ; 
 int /*<<< orphan*/  task_css (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pids_release(struct task_struct *task)
{
	struct pids_cgroup *pids = css_pids(task_css(task, pids_cgrp_id));

	pids_uncharge(pids, 1);
}
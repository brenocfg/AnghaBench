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
struct seq_file {int dummy; } ;
struct cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct cgroup* cgroup; } ;

/* Variables and functions */
 int CSS_TASK_ITER_PROCS ; 
 int CSS_TASK_ITER_THREADED ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cgroup_procs_start (struct seq_file*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cgroup_is_threaded (struct cgroup*) ; 
 TYPE_1__* seq_css (struct seq_file*) ; 

__attribute__((used)) static void *cgroup_procs_start(struct seq_file *s, loff_t *pos)
{
	struct cgroup *cgrp = seq_css(s)->cgroup;

	/*
	 * All processes of a threaded subtree belong to the domain cgroup
	 * of the subtree.  Only threads can be distributed across the
	 * subtree.  Reject reads on cgroup.procs in the subtree proper.
	 * They're always empty anyway.
	 */
	if (cgroup_is_threaded(cgrp))
		return ERR_PTR(-EOPNOTSUPP);

	return __cgroup_procs_start(s, pos, CSS_TASK_ITER_PROCS |
					    CSS_TASK_ITER_THREADED);
}
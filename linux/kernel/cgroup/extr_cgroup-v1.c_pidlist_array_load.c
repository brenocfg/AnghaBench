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
struct css_task_iter {int dummy; } ;
struct cgroup_pidlist {int* list; int length; } ;
struct cgroup {int /*<<< orphan*/  self; int /*<<< orphan*/  pidlist_mutex; } ;
typedef  int pid_t ;
typedef  enum cgroup_filetype { ____Placeholder_cgroup_filetype } cgroup_filetype ;

/* Variables and functions */
 int CGROUP_FILE_PROCS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cgroup_pidlist* cgroup_pidlist_find_create (struct cgroup*,int) ; 
 int cgroup_task_count (struct cgroup*) ; 
 int /*<<< orphan*/  cmppid ; 
 int /*<<< orphan*/  css_task_iter_end (struct css_task_iter*) ; 
 struct task_struct* css_task_iter_next (struct css_task_iter*) ; 
 int /*<<< orphan*/  css_task_iter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct css_task_iter*) ; 
 int /*<<< orphan*/  kvfree (int*) ; 
 int* kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int pidlist_uniq (int*,int) ; 
 int /*<<< orphan*/  sort (int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int task_pid_vnr (struct task_struct*) ; 
 int task_tgid_vnr (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pidlist_array_load(struct cgroup *cgrp, enum cgroup_filetype type,
			      struct cgroup_pidlist **lp)
{
	pid_t *array;
	int length;
	int pid, n = 0; /* used for populating the array */
	struct css_task_iter it;
	struct task_struct *tsk;
	struct cgroup_pidlist *l;

	lockdep_assert_held(&cgrp->pidlist_mutex);

	/*
	 * If cgroup gets more users after we read count, we won't have
	 * enough space - tough.  This race is indistinguishable to the
	 * caller from the case that the additional cgroup users didn't
	 * show up until sometime later on.
	 */
	length = cgroup_task_count(cgrp);
	array = kvmalloc_array(length, sizeof(pid_t), GFP_KERNEL);
	if (!array)
		return -ENOMEM;
	/* now, populate the array */
	css_task_iter_start(&cgrp->self, 0, &it);
	while ((tsk = css_task_iter_next(&it))) {
		if (unlikely(n == length))
			break;
		/* get tgid or pid for procs or tasks file respectively */
		if (type == CGROUP_FILE_PROCS)
			pid = task_tgid_vnr(tsk);
		else
			pid = task_pid_vnr(tsk);
		if (pid > 0) /* make sure to only use valid results */
			array[n++] = pid;
	}
	css_task_iter_end(&it);
	length = n;
	/* now sort & (if procs) strip out duplicates */
	sort(array, length, sizeof(pid_t), cmppid, NULL);
	if (type == CGROUP_FILE_PROCS)
		length = pidlist_uniq(array, length);

	l = cgroup_pidlist_find_create(cgrp, type);
	if (!l) {
		kvfree(array);
		return -ENOMEM;
	}

	/* store array, freeing old if necessary */
	kvfree(l->list);
	l->list = array;
	l->length = length;
	*lp = l;
	return 0;
}
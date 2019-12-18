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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct task_struct {int /*<<< orphan*/  files; } ;
struct css_task_iter {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cgroup_cls_state {scalar_t__ classid; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_sk_alloc_disable () ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct cgroup_cls_state* css_cls_state (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  css_task_iter_end (struct css_task_iter*) ; 
 struct task_struct* css_task_iter_next (struct css_task_iter*) ; 
 int /*<<< orphan*/  css_task_iter_start (struct cgroup_subsys_state*,int /*<<< orphan*/ ,struct css_task_iter*) ; 
 int /*<<< orphan*/  iterate_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  update_classid_sock ; 

__attribute__((used)) static int write_classid(struct cgroup_subsys_state *css, struct cftype *cft,
			 u64 value)
{
	struct cgroup_cls_state *cs = css_cls_state(css);
	struct css_task_iter it;
	struct task_struct *p;

	cgroup_sk_alloc_disable();

	cs->classid = (u32)value;

	css_task_iter_start(css, 0, &it);
	while ((p = css_task_iter_next(&it))) {
		task_lock(p);
		iterate_fd(p->files, 0, update_classid_sock,
			   (void *)(unsigned long)cs->classid);
		task_unlock(p);
		cond_resched();
	}
	css_task_iter_end(&it);

	return 0;
}
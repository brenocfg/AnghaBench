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
struct task_struct {int /*<<< orphan*/  mm; } ;
struct mem_cgroup {int /*<<< orphan*/  css; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 struct task_struct* find_lock_task_mm (struct task_struct*) ; 
 struct mem_cgroup* get_mem_cgroup_from_mm (int /*<<< orphan*/ ) ; 
 struct mem_cgroup* mem_cgroup_from_task (struct task_struct*) ; 
 int mem_cgroup_is_descendant (struct mem_cgroup*,struct mem_cgroup*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

bool task_in_mem_cgroup(struct task_struct *task, struct mem_cgroup *memcg)
{
	struct mem_cgroup *task_memcg;
	struct task_struct *p;
	bool ret;

	p = find_lock_task_mm(task);
	if (p) {
		task_memcg = get_mem_cgroup_from_mm(p->mm);
		task_unlock(p);
	} else {
		/*
		 * All threads may have already detached their mm's, but the oom
		 * killer still needs to detect if they have already been oom
		 * killed to prevent needlessly killing additional tasks.
		 */
		rcu_read_lock();
		task_memcg = mem_cgroup_from_task(task);
		css_get(&task_memcg->css);
		rcu_read_unlock();
	}
	ret = mem_cgroup_is_descendant(task_memcg, memcg);
	css_put(&task_memcg->css);
	return ret;
}
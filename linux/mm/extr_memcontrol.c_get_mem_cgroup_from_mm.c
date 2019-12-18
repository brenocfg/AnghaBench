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
struct mm_struct {int /*<<< orphan*/  owner; } ;
struct mem_cgroup {int /*<<< orphan*/  css; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_tryget_online (int /*<<< orphan*/ *) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 struct mem_cgroup* mem_cgroup_from_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct mem_cgroup* root_mem_cgroup ; 
 scalar_t__ unlikely (int) ; 

struct mem_cgroup *get_mem_cgroup_from_mm(struct mm_struct *mm)
{
	struct mem_cgroup *memcg;

	if (mem_cgroup_disabled())
		return NULL;

	rcu_read_lock();
	do {
		/*
		 * Page cache insertions can happen withou an
		 * actual mm context, e.g. during disk probing
		 * on boot, loopback IO, acct() writes etc.
		 */
		if (unlikely(!mm))
			memcg = root_mem_cgroup;
		else {
			memcg = mem_cgroup_from_task(rcu_dereference(mm->owner));
			if (unlikely(!memcg))
				memcg = root_mem_cgroup;
		}
	} while (!css_tryget_online(&memcg->css));
	rcu_read_unlock();
	return memcg;
}
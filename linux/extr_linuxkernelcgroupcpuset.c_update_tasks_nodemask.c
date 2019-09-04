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
struct mm_struct {int dummy; } ;
struct css_task_iter {int dummy; } ;
struct cpuset {int /*<<< orphan*/  old_mems_allowed; int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  css; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 struct cpuset* cpuset_being_rebound ; 
 int /*<<< orphan*/  cpuset_change_task_nodemask (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuset_migrate_mm (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_task_iter_end (struct css_task_iter*) ; 
 struct task_struct* css_task_iter_next (struct css_task_iter*) ; 
 int /*<<< orphan*/  css_task_iter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct css_task_iter*) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  guarantee_online_mems (struct cpuset*,int /*<<< orphan*/ *) ; 
 int is_memory_migrate (struct cpuset*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  mpol_rebind_mm (struct mm_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_tasks_nodemask(struct cpuset *cs)
{
	static nodemask_t newmems;	/* protected by cpuset_mutex */
	struct css_task_iter it;
	struct task_struct *task;

	cpuset_being_rebound = cs;		/* causes mpol_dup() rebind */

	guarantee_online_mems(cs, &newmems);

	/*
	 * The mpol_rebind_mm() call takes mmap_sem, which we couldn't
	 * take while holding tasklist_lock.  Forks can happen - the
	 * mpol_dup() cpuset_being_rebound check will catch such forks,
	 * and rebind their vma mempolicies too.  Because we still hold
	 * the global cpuset_mutex, we know that no other rebind effort
	 * will be contending for the global variable cpuset_being_rebound.
	 * It's ok if we rebind the same mm twice; mpol_rebind_mm()
	 * is idempotent.  Also migrate pages in each mm to new nodes.
	 */
	css_task_iter_start(&cs->css, 0, &it);
	while ((task = css_task_iter_next(&it))) {
		struct mm_struct *mm;
		bool migrate;

		cpuset_change_task_nodemask(task, &newmems);

		mm = get_task_mm(task);
		if (!mm)
			continue;

		migrate = is_memory_migrate(cs);

		mpol_rebind_mm(mm, &cs->mems_allowed);
		if (migrate)
			cpuset_migrate_mm(mm, &cs->old_mems_allowed, &newmems);
		else
			mmput(mm);
	}
	css_task_iter_end(&it);

	/*
	 * All the tasks' nodemasks have been updated, update
	 * cs->old_mems_allowed.
	 */
	cs->old_mems_allowed = newmems;

	/* We're done rebinding vmas to this cpuset's new mems_allowed. */
	cpuset_being_rebound = NULL;
}
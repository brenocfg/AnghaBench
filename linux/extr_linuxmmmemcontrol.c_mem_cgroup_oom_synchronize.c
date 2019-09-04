#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  entry; TYPE_3__* private; int /*<<< orphan*/  func; scalar_t__ flags; } ;
struct oom_wait_info {TYPE_1__ wait; struct mem_cgroup* memcg; } ;
struct mem_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/  oom_kill_disable; } ;
struct TYPE_5__ {struct mem_cgroup* memcg_in_oom; int /*<<< orphan*/  memcg_oom_order; int /*<<< orphan*/  memcg_oom_gfp_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mem_cgroup_mark_under_oom (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_oom_notify (struct mem_cgroup*) ; 
 int mem_cgroup_oom_trylock (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_oom_unlock (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_out_of_memory (struct mem_cgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_unmark_under_oom (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_oom_recover (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_oom_waitq ; 
 int /*<<< orphan*/  memcg_oom_wake_function ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 

bool mem_cgroup_oom_synchronize(bool handle)
{
	struct mem_cgroup *memcg = current->memcg_in_oom;
	struct oom_wait_info owait;
	bool locked;

	/* OOM is global, do not handle */
	if (!memcg)
		return false;

	if (!handle)
		goto cleanup;

	owait.memcg = memcg;
	owait.wait.flags = 0;
	owait.wait.func = memcg_oom_wake_function;
	owait.wait.private = current;
	INIT_LIST_HEAD(&owait.wait.entry);

	prepare_to_wait(&memcg_oom_waitq, &owait.wait, TASK_KILLABLE);
	mem_cgroup_mark_under_oom(memcg);

	locked = mem_cgroup_oom_trylock(memcg);

	if (locked)
		mem_cgroup_oom_notify(memcg);

	if (locked && !memcg->oom_kill_disable) {
		mem_cgroup_unmark_under_oom(memcg);
		finish_wait(&memcg_oom_waitq, &owait.wait);
		mem_cgroup_out_of_memory(memcg, current->memcg_oom_gfp_mask,
					 current->memcg_oom_order);
	} else {
		schedule();
		mem_cgroup_unmark_under_oom(memcg);
		finish_wait(&memcg_oom_waitq, &owait.wait);
	}

	if (locked) {
		mem_cgroup_oom_unlock(memcg);
		/*
		 * There is no guarantee that an OOM-lock contender
		 * sees the wakeups triggered by the OOM kill
		 * uncharges.  Wake any sleepers explicitely.
		 */
		memcg_oom_recover(memcg);
	}
cleanup:
	current->memcg_in_oom = NULL;
	css_put(&memcg->css);
	return true;
}
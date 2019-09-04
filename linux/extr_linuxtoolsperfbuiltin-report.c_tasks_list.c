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
struct thread {int ppid; } ;
struct task {int /*<<< orphan*/  children; int /*<<< orphan*/  list; struct thread* thread; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct task* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct thread* machine__find_thread (struct machine*,int,int) ; 
 struct task* thread__priv (struct thread*) ; 

__attribute__((used)) static struct task *tasks_list(struct task *task, struct machine *machine)
{
	struct thread *parent_thread, *thread = task->thread;
	struct task   *parent_task;

	/* Already listed. */
	if (!list_empty(&task->list))
		return NULL;

	/* Last one in the chain. */
	if (thread->ppid == -1)
		return task;

	parent_thread = machine__find_thread(machine, -1, thread->ppid);
	if (!parent_thread)
		return ERR_PTR(-ENOENT);

	parent_task = thread__priv(parent_thread);
	list_add_tail(&task->list, &parent_task->children);
	return tasks_list(parent_task, machine);
}
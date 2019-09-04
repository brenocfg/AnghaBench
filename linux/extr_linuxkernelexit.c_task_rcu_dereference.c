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
struct task_struct {int /*<<< orphan*/  sighand; } ;
struct sighand_struct {int dummy; } ;

/* Variables and functions */
 struct task_struct* READ_ONCE (struct task_struct*) ; 
 int /*<<< orphan*/  probe_kernel_address (int /*<<< orphan*/ *,struct sighand_struct*) ; 
 struct task_struct* rcu_dereference (struct task_struct*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ unlikely (int) ; 

struct task_struct *task_rcu_dereference(struct task_struct **ptask)
{
	struct sighand_struct *sighand;
	struct task_struct *task;

	/*
	 * We need to verify that release_task() was not called and thus
	 * delayed_put_task_struct() can't run and drop the last reference
	 * before rcu_read_unlock(). We check task->sighand != NULL,
	 * but we can read the already freed and reused memory.
	 */
retry:
	task = rcu_dereference(*ptask);
	if (!task)
		return NULL;

	probe_kernel_address(&task->sighand, sighand);

	/*
	 * Pairs with atomic_dec_and_test() in put_task_struct(). If this task
	 * was already freed we can not miss the preceding update of this
	 * pointer.
	 */
	smp_rmb();
	if (unlikely(task != READ_ONCE(*ptask)))
		goto retry;

	/*
	 * We've re-checked that "task == *ptask", now we have two different
	 * cases:
	 *
	 * 1. This is actually the same task/task_struct. In this case
	 *    sighand != NULL tells us it is still alive.
	 *
	 * 2. This is another task which got the same memory for task_struct.
	 *    We can't know this of course, and we can not trust
	 *    sighand != NULL.
	 *
	 *    In this case we actually return a random value, but this is
	 *    correct.
	 *
	 *    If we return NULL - we can pretend that we actually noticed that
	 *    *ptask was updated when the previous task has exited. Or pretend
	 *    that probe_slab_address(&sighand) reads NULL.
	 *
	 *    If we return the new task (because sighand is not NULL for any
	 *    reason) - this is fine too. This (new) task can't go away before
	 *    another gp pass.
	 *
	 *    And note: We could even eliminate the false positive if re-read
	 *    task->sighand once again to avoid the falsely NULL. But this case
	 *    is very unlikely so we don't care.
	 */
	if (!sighand)
		return NULL;

	return task;
}
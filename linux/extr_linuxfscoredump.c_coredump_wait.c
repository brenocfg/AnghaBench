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
struct task_struct {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  core_state; } ;
struct core_thread {struct core_thread* next; int /*<<< orphan*/  task; } ;
struct TYPE_2__ {struct core_thread* next; struct task_struct* task; } ;
struct core_state {TYPE_1__ dumper; int /*<<< orphan*/  startup; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 struct task_struct* current ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freezer_count () ; 
 int /*<<< orphan*/  freezer_do_not_count () ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_task_inactive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zap_threads (struct task_struct*,struct mm_struct*,struct core_state*,int) ; 

__attribute__((used)) static int coredump_wait(int exit_code, struct core_state *core_state)
{
	struct task_struct *tsk = current;
	struct mm_struct *mm = tsk->mm;
	int core_waiters = -EBUSY;

	init_completion(&core_state->startup);
	core_state->dumper.task = tsk;
	core_state->dumper.next = NULL;

	if (down_write_killable(&mm->mmap_sem))
		return -EINTR;

	if (!mm->core_state)
		core_waiters = zap_threads(tsk, mm, core_state, exit_code);
	up_write(&mm->mmap_sem);

	if (core_waiters > 0) {
		struct core_thread *ptr;

		freezer_do_not_count();
		wait_for_completion(&core_state->startup);
		freezer_count();
		/*
		 * Wait for all the threads to become inactive, so that
		 * all the thread context (extended register state, like
		 * fpu etc) gets copied to the memory.
		 */
		ptr = core_state->dumper.next;
		while (ptr != NULL) {
			wait_task_inactive(ptr->task, 0);
			ptr = ptr->next;
		}
	}

	return core_waiters;
}
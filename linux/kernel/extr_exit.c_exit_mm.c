#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct core_state* core_state; } ;
struct core_thread {TYPE_2__* task; int /*<<< orphan*/  next; } ;
struct TYPE_7__ {int /*<<< orphan*/  next; } ;
struct core_state {int /*<<< orphan*/  startup; int /*<<< orphan*/  nr_threads; TYPE_1__ dumper; } ;
struct TYPE_8__ {struct mm_struct* mm; struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enter_lazy_tlb (struct mm_struct*,TYPE_2__*) ; 
 int /*<<< orphan*/  exit_oom_victim () ; 
 int /*<<< orphan*/  freezable_schedule () ; 
 int /*<<< orphan*/  mm_release (TYPE_2__*,struct mm_struct*) ; 
 int /*<<< orphan*/  mm_update_next_owner (struct mm_struct*) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_mm_rss (struct mm_struct*) ; 
 int /*<<< orphan*/  task_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_2__*) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,struct core_thread*) ; 

__attribute__((used)) static void exit_mm(void)
{
	struct mm_struct *mm = current->mm;
	struct core_state *core_state;

	mm_release(current, mm);
	if (!mm)
		return;
	sync_mm_rss(mm);
	/*
	 * Serialize with any possible pending coredump.
	 * We must hold mmap_sem around checking core_state
	 * and clearing tsk->mm.  The core-inducing thread
	 * will increment ->nr_threads for each thread in the
	 * group with ->mm != NULL.
	 */
	down_read(&mm->mmap_sem);
	core_state = mm->core_state;
	if (core_state) {
		struct core_thread self;

		up_read(&mm->mmap_sem);

		self.task = current;
		self.next = xchg(&core_state->dumper.next, &self);
		/*
		 * Implies mb(), the result of xchg() must be visible
		 * to core_state->dumper.
		 */
		if (atomic_dec_and_test(&core_state->nr_threads))
			complete(&core_state->startup);

		for (;;) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			if (!self.task) /* see coredump_finish() */
				break;
			freezable_schedule();
		}
		__set_current_state(TASK_RUNNING);
		down_read(&mm->mmap_sem);
	}
	mmgrab(mm);
	BUG_ON(mm != current->active_mm);
	/* more a memory barrier than a real lock */
	task_lock(current);
	current->mm = NULL;
	up_read(&mm->mmap_sem);
	enter_lazy_tlb(mm, current);
	task_unlock(current);
	mm_update_next_owner(mm);
	mmput(mm);
	if (test_thread_flag(TIF_MEMDIE))
		exit_oom_victim();
}
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
struct task_struct {int /*<<< orphan*/  pid; TYPE_1__* signal; struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  oom_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMF_OOM_VICTIM ; 
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __thaw_task (struct task_struct*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mm_struct*) ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oom_killer_disabled ; 
 int /*<<< orphan*/  oom_victims ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mark_victim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_oom_victim(struct task_struct *tsk)
{
	struct mm_struct *mm = tsk->mm;

	WARN_ON(oom_killer_disabled);
	/* OOM killer might race with memcg OOM */
	if (test_and_set_tsk_thread_flag(tsk, TIF_MEMDIE))
		return;

	/* oom_mm is bound to the signal struct life time. */
	if (!cmpxchg(&tsk->signal->oom_mm, NULL, mm)) {
		mmgrab(tsk->signal->oom_mm);
		set_bit(MMF_OOM_VICTIM, &mm->flags);
	}

	/*
	 * Make sure that the task is woken up from uninterruptible sleep
	 * if it is frozen because OOM killer wouldn't be able to free
	 * any memory and livelock. freezing_slow_path will tell the freezer
	 * that TIF_MEMDIE tasks should be ignored.
	 */
	__thaw_task(tsk);
	atomic_inc(&oom_victims);
	trace_mark_victim(tsk->pid);
}
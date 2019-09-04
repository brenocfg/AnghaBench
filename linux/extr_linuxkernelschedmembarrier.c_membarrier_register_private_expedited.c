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
struct task_struct {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  membarrier_state; int /*<<< orphan*/  mm_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARCH_HAS_MEMBARRIER_SYNC_CORE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MEMBARRIER_FLAG_SYNC_CORE ; 
 int MEMBARRIER_STATE_PRIVATE_EXPEDITED ; 
 int MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY ; 
 int MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE ; 
 int MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY ; 
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int get_nr_threads (struct task_struct*) ; 
 int /*<<< orphan*/  synchronize_sched () ; 

__attribute__((used)) static int membarrier_register_private_expedited(int flags)
{
	struct task_struct *p = current;
	struct mm_struct *mm = p->mm;
	int state = MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY;

	if (flags & MEMBARRIER_FLAG_SYNC_CORE) {
		if (!IS_ENABLED(CONFIG_ARCH_HAS_MEMBARRIER_SYNC_CORE))
			return -EINVAL;
		state = MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY;
	}

	/*
	 * We need to consider threads belonging to different thread
	 * groups, which use the same mm. (CLONE_VM but not
	 * CLONE_THREAD).
	 */
	if (atomic_read(&mm->membarrier_state) & state)
		return 0;
	atomic_or(MEMBARRIER_STATE_PRIVATE_EXPEDITED, &mm->membarrier_state);
	if (flags & MEMBARRIER_FLAG_SYNC_CORE)
		atomic_or(MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE,
			  &mm->membarrier_state);
	if (!(atomic_read(&mm->mm_users) == 1 && get_nr_threads(p) == 1)) {
		/*
		 * Ensure all future scheduler executions will observe the
		 * new thread flag state for this process.
		 */
		synchronize_sched();
	}
	atomic_or(state, &mm->membarrier_state);

	return 0;
}
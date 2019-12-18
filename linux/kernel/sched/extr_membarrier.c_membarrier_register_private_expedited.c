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
struct mm_struct {int /*<<< orphan*/  membarrier_state; } ;

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
 int sync_runqueues_membarrier_state (struct mm_struct*) ; 

__attribute__((used)) static int membarrier_register_private_expedited(int flags)
{
	struct task_struct *p = current;
	struct mm_struct *mm = p->mm;
	int ready_state = MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY,
	    set_state = MEMBARRIER_STATE_PRIVATE_EXPEDITED,
	    ret;

	if (flags & MEMBARRIER_FLAG_SYNC_CORE) {
		if (!IS_ENABLED(CONFIG_ARCH_HAS_MEMBARRIER_SYNC_CORE))
			return -EINVAL;
		ready_state =
			MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY;
	}

	/*
	 * We need to consider threads belonging to different thread
	 * groups, which use the same mm. (CLONE_VM but not
	 * CLONE_THREAD).
	 */
	if ((atomic_read(&mm->membarrier_state) & ready_state) == ready_state)
		return 0;
	if (flags & MEMBARRIER_FLAG_SYNC_CORE)
		set_state |= MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE;
	atomic_or(set_state, &mm->membarrier_state);
	ret = sync_runqueues_membarrier_state(mm);
	if (ret)
		return ret;
	atomic_or(ready_state, &mm->membarrier_state);

	return 0;
}
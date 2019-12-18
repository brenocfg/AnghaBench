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
 int MEMBARRIER_STATE_GLOBAL_EXPEDITED ; 
 int MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY ; 
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int sync_runqueues_membarrier_state (struct mm_struct*) ; 

__attribute__((used)) static int membarrier_register_global_expedited(void)
{
	struct task_struct *p = current;
	struct mm_struct *mm = p->mm;
	int ret;

	if (atomic_read(&mm->membarrier_state) &
	    MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY)
		return 0;
	atomic_or(MEMBARRIER_STATE_GLOBAL_EXPEDITED, &mm->membarrier_state);
	ret = sync_runqueues_membarrier_state(mm);
	if (ret)
		return ret;
	atomic_or(MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY,
		  &mm->membarrier_state);

	return 0;
}
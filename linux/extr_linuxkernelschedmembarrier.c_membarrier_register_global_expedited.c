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
 int MEMBARRIER_STATE_GLOBAL_EXPEDITED ; 
 int MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY ; 
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int get_nr_threads (struct task_struct*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  synchronize_sched () ; 

__attribute__((used)) static int membarrier_register_global_expedited(void)
{
	struct task_struct *p = current;
	struct mm_struct *mm = p->mm;

	if (atomic_read(&mm->membarrier_state) &
	    MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY)
		return 0;
	atomic_or(MEMBARRIER_STATE_GLOBAL_EXPEDITED, &mm->membarrier_state);
	if (atomic_read(&mm->mm_users) == 1 && get_nr_threads(p) == 1) {
		/*
		 * For single mm user, single threaded process, we can
		 * simply issue a memory barrier after setting
		 * MEMBARRIER_STATE_GLOBAL_EXPEDITED to guarantee that
		 * no memory access following registration is reordered
		 * before registration.
		 */
		smp_mb();
	} else {
		/*
		 * For multi-mm user threads, we need to ensure all
		 * future scheduler executions will observe the new
		 * thread flag state for this mm.
		 */
		synchronize_sched();
	}
	atomic_or(MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY,
		  &mm->membarrier_state);

	return 0;
}
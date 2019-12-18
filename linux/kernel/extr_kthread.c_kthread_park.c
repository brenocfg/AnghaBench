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
struct task_struct {int flags; } ;
struct kthread {int /*<<< orphan*/  parked; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOSYS ; 
 int /*<<< orphan*/  KTHREAD_SHOULD_PARK ; 
 int PF_EXITING ; 
 int /*<<< orphan*/  TASK_PARKED ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct kthread* to_kthread (struct task_struct*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_task_inactive (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int kthread_park(struct task_struct *k)
{
	struct kthread *kthread = to_kthread(k);

	if (WARN_ON(k->flags & PF_EXITING))
		return -ENOSYS;

	if (WARN_ON_ONCE(test_bit(KTHREAD_SHOULD_PARK, &kthread->flags)))
		return -EBUSY;

	set_bit(KTHREAD_SHOULD_PARK, &kthread->flags);
	if (k != current) {
		wake_up_process(k);
		/*
		 * Wait for __kthread_parkme() to complete(), this means we
		 * _will_ have TASK_PARKED and are about to call schedule().
		 */
		wait_for_completion(&kthread->parked);
		/*
		 * Now wait for that schedule() to complete and the task to
		 * get scheduled out.
		 */
		WARN_ON_ONCE(!wait_task_inactive(k, TASK_PARKED));
	}

	return 0;
}
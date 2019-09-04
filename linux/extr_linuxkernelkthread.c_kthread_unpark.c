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
struct task_struct {int dummy; } ;
struct kthread {int /*<<< orphan*/  flags; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTHREAD_IS_PER_CPU ; 
 int /*<<< orphan*/  KTHREAD_SHOULD_PARK ; 
 int /*<<< orphan*/  TASK_PARKED ; 
 int /*<<< orphan*/  __kthread_bind (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct kthread* to_kthread (struct task_struct*) ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 

void kthread_unpark(struct task_struct *k)
{
	struct kthread *kthread = to_kthread(k);

	/*
	 * Newly created kthread was parked when the CPU was offline.
	 * The binding was lost and we need to set it again.
	 */
	if (test_bit(KTHREAD_IS_PER_CPU, &kthread->flags))
		__kthread_bind(k, kthread->cpu, TASK_PARKED);

	clear_bit(KTHREAD_SHOULD_PARK, &kthread->flags);
	/*
	 * __kthread_parkme() will either see !SHOULD_PARK or get the wakeup.
	 */
	wake_up_state(k, TASK_PARKED);
}
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
struct task_struct {int jobctl; } ;

/* Variables and functions */
 int JOBCTL_TRAPPING ; 
 int /*<<< orphan*/  JOBCTL_TRAPPING_BIT ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_bit (int*,int /*<<< orphan*/ ) ; 

void task_clear_jobctl_trapping(struct task_struct *task)
{
	if (unlikely(task->jobctl & JOBCTL_TRAPPING)) {
		task->jobctl &= ~JOBCTL_TRAPPING;
		smp_mb();	/* advised by wake_up_bit() */
		wake_up_bit(&task->jobctl, JOBCTL_TRAPPING_BIT);
	}
}
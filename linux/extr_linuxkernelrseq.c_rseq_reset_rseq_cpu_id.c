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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {TYPE_1__* rseq; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_id; int /*<<< orphan*/  cpu_id_start; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  RSEQ_CPU_ID_UNINITIALIZED ; 
 scalar_t__ put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rseq_reset_rseq_cpu_id(struct task_struct *t)
{
	u32 cpu_id_start = 0, cpu_id = RSEQ_CPU_ID_UNINITIALIZED;

	/*
	 * Reset cpu_id_start to its initial state (0).
	 */
	if (put_user(cpu_id_start, &t->rseq->cpu_id_start))
		return -EFAULT;
	/*
	 * Reset cpu_id to RSEQ_CPU_ID_UNINITIALIZED, so any user coming
	 * in after unregistration can figure out that rseq needs to be
	 * registered again.
	 */
	if (put_user(cpu_id, &t->rseq->cpu_id))
		return -EFAULT;
	return 0;
}
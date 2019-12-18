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
 scalar_t__ put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  trace_rseq_update (struct task_struct*) ; 

__attribute__((used)) static int rseq_update_cpu_id(struct task_struct *t)
{
	u32 cpu_id = raw_smp_processor_id();

	if (put_user(cpu_id, &t->rseq->cpu_id_start))
		return -EFAULT;
	if (put_user(cpu_id, &t->rseq->cpu_id))
		return -EFAULT;
	trace_rseq_update(t);
	return 0;
}
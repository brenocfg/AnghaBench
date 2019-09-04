#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  info; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ call_single_data_t ;

/* Variables and functions */
 int CSD_FLAG_LOCK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  csd_lock_wait (TYPE_1__*) ; 
 int generic_exec_single (int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_wmb () ; 

int smp_call_function_single_async(int cpu, call_single_data_t *csd)
{
	int err = 0;

	preempt_disable();

	/* We could deadlock if we have to wait here with interrupts disabled! */
	if (WARN_ON_ONCE(csd->flags & CSD_FLAG_LOCK))
		csd_lock_wait(csd);

	csd->flags = CSD_FLAG_LOCK;
	smp_wmb();

	err = generic_exec_single(cpu, csd, csd->func, csd->info);
	preempt_enable();

	return err;
}
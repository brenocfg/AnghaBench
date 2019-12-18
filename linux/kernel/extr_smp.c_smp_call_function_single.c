#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  smp_call_func_t ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ call_single_data_t ;

/* Variables and functions */
 int CSD_FLAG_LOCK ; 
 int CSD_FLAG_SYNCHRONOUS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  csd_data ; 
 int /*<<< orphan*/  csd_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  csd_lock_wait (TYPE_1__*) ; 
 int generic_exec_single (int,TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  in_task () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  oops_in_progress ; 
 int /*<<< orphan*/  put_cpu () ; 
 TYPE_1__* this_cpu_ptr (int /*<<< orphan*/ *) ; 

int smp_call_function_single(int cpu, smp_call_func_t func, void *info,
			     int wait)
{
	call_single_data_t *csd;
	call_single_data_t csd_stack = {
		.flags = CSD_FLAG_LOCK | CSD_FLAG_SYNCHRONOUS,
	};
	int this_cpu;
	int err;

	/*
	 * prevent preemption and reschedule on another processor,
	 * as well as CPU removal
	 */
	this_cpu = get_cpu();

	/*
	 * Can deadlock when called with interrupts disabled.
	 * We allow cpu's that are not yet online though, as no one else can
	 * send smp call function interrupt to this cpu and as such deadlocks
	 * can't happen.
	 */
	WARN_ON_ONCE(cpu_online(this_cpu) && irqs_disabled()
		     && !oops_in_progress);

	/*
	 * When @wait we can deadlock when we interrupt between llist_add() and
	 * arch_send_call_function_ipi*(); when !@wait we can deadlock due to
	 * csd_lock() on because the interrupt context uses the same csd
	 * storage.
	 */
	WARN_ON_ONCE(!in_task());

	csd = &csd_stack;
	if (!wait) {
		csd = this_cpu_ptr(&csd_data);
		csd_lock(csd);
	}

	err = generic_exec_single(cpu, csd, func, info);

	if (wait)
		csd_lock_wait(csd);

	put_cpu();

	return err;
}
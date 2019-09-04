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
struct qman_cgr {size_t cgrid; } ;

/* Variables and functions */
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__* qman_cgr_cpus ; 
 int /*<<< orphan*/  qman_delete_cgr (struct qman_cgr*) ; 
 int /*<<< orphan*/  qman_delete_cgr_smp_call ; 
 int /*<<< orphan*/  smp_call_function_single (scalar_t__,int /*<<< orphan*/ ,struct qman_cgr*,int) ; 
 scalar_t__ smp_processor_id () ; 

void qman_delete_cgr_safe(struct qman_cgr *cgr)
{
	preempt_disable();
	if (qman_cgr_cpus[cgr->cgrid] != smp_processor_id()) {
		smp_call_function_single(qman_cgr_cpus[cgr->cgrid],
					 qman_delete_cgr_smp_call, cgr, true);
		preempt_enable();
		return;
	}

	qman_delete_cgr(cgr);
	preempt_enable();
}
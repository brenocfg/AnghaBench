#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_event_attr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  disabled; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__* ctx; } ;
struct TYPE_3__ {scalar_t__ task; } ;

/* Variables and functions */
 scalar_t__ current ; 
 scalar_t__ irqs_disabled () ; 
 int modify_user_hw_breakpoint_check (struct perf_event*,struct perf_event_attr*,int) ; 
 int /*<<< orphan*/  perf_event_disable (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_disable_local (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_enable (struct perf_event*) ; 

int modify_user_hw_breakpoint(struct perf_event *bp, struct perf_event_attr *attr)
{
	int err;

	/*
	 * modify_user_hw_breakpoint can be invoked with IRQs disabled and hence it
	 * will not be possible to raise IPIs that invoke __perf_event_disable.
	 * So call the function directly after making sure we are targeting the
	 * current task.
	 */
	if (irqs_disabled() && bp->ctx && bp->ctx->task == current)
		perf_event_disable_local(bp);
	else
		perf_event_disable(bp);

	err = modify_user_hw_breakpoint_check(bp, attr, false);

	if (!bp->attr.disabled)
		perf_event_enable(bp);

	return err;
}
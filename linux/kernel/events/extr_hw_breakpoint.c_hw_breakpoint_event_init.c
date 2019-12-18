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
struct TYPE_2__ {scalar_t__ type; } ;
struct perf_event {int /*<<< orphan*/  destroy; TYPE_1__ attr; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 scalar_t__ PERF_TYPE_BREAKPOINT ; 
 int /*<<< orphan*/  bp_perf_event_destroy ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int register_perf_hw_breakpoint (struct perf_event*) ; 

__attribute__((used)) static int hw_breakpoint_event_init(struct perf_event *bp)
{
	int err;

	if (bp->attr.type != PERF_TYPE_BREAKPOINT)
		return -ENOENT;

	/*
	 * no branch sampling for breakpoint events
	 */
	if (has_branch_stack(bp))
		return -EOPNOTSUPP;

	err = register_perf_hw_breakpoint(bp);
	if (err)
		return err;

	bp->destroy = bp_perf_event_destroy;

	return 0;
}
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
struct perf_event_attr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  disabled; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _perf_event_disable (struct perf_event*) ; 
 int /*<<< orphan*/  _perf_event_enable (struct perf_event*) ; 
 int modify_user_hw_breakpoint_check (struct perf_event*,struct perf_event_attr*,int) ; 

__attribute__((used)) static int perf_event_modify_breakpoint(struct perf_event *bp,
					 struct perf_event_attr *attr)
{
	int err;

	_perf_event_disable(bp);

	err = modify_user_hw_breakpoint_check(bp, attr, true);

	if (!bp->attr.disabled)
		_perf_event_enable(bp);

	return err;
}
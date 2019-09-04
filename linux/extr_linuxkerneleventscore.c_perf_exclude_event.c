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
struct pt_regs {int dummy; } ;
struct TYPE_4__ {scalar_t__ exclude_kernel; scalar_t__ exclude_user; } ;
struct TYPE_3__ {int state; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__ hw; } ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int perf_exclude_event(struct perf_event *event,
			      struct pt_regs *regs)
{
	if (event->hw.state & PERF_HES_STOPPED)
		return 1;

	if (regs) {
		if (event->attr.exclude_user && user_mode(regs))
			return 1;

		if (event->attr.exclude_kernel && !user_mode(regs))
			return 1;
	}

	return 0;
}
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
typedef  scalar_t__ suspend_state_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* restore_early ) () ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* wake ) () ;} ;

/* Variables and functions */
 scalar_t__ PM_SUSPEND_TO_IDLE ; 
 TYPE_2__* s2idle_ops ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 TYPE_1__* suspend_ops ; 

__attribute__((used)) static void platform_resume_noirq(suspend_state_t state)
{
	if (state == PM_SUSPEND_TO_IDLE) {
		if (s2idle_ops && s2idle_ops->restore_early)
			s2idle_ops->restore_early();
	} else if (suspend_ops->wake) {
		suspend_ops->wake();
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fired; scalar_t__ armed; } ;
typedef  TYPE_1__ REMOTE_EVENT_T ;

/* Variables and functions */
 scalar_t__ BELL2 ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 scalar_t__ g_regs ; 
 int /*<<< orphan*/  sy ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void
remote_event_signal(REMOTE_EVENT_T *event)
{
	wmb();

	event->fired = 1;

	dsb(sy);         /* data barrier operation */

	if (event->armed)
		writel(0, g_regs + BELL2); /* trigger vc interrupt */
}
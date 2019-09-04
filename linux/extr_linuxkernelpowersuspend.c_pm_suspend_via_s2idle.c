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

/* Variables and functions */
 scalar_t__ PM_SUSPEND_TO_IDLE ; 
 scalar_t__ mem_sleep_current ; 

bool pm_suspend_via_s2idle(void)
{
	return mem_sleep_current == PM_SUSPEND_TO_IDLE;
}
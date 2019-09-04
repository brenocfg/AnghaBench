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
typedef  enum sclp_pm_event { ____Placeholder_sclp_pm_event } sclp_pm_event ;

/* Variables and functions */
#define  SCLP_PM_EVENT_FREEZE 130 
#define  SCLP_PM_EVENT_RESTORE 129 
#define  SCLP_PM_EVENT_THAW 128 
 int /*<<< orphan*/  sclp_console_resume () ; 
 int /*<<< orphan*/  sclp_console_suspend () ; 

void sclp_console_pm_event(enum sclp_pm_event sclp_pm_event)
{
	switch (sclp_pm_event) {
	case SCLP_PM_EVENT_FREEZE:
		sclp_console_suspend();
		break;
	case SCLP_PM_EVENT_RESTORE:
	case SCLP_PM_EVENT_THAW:
		sclp_console_resume();
		break;
	}
}
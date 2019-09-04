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
struct alarm {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum alarmtimer_restart { ____Placeholder_alarmtimer_restart } alarmtimer_restart ;

/* Variables and functions */
 int ALARMTIMER_NORESTART ; 
 int cm_timer_set ; 

__attribute__((used)) static enum alarmtimer_restart cm_timer_func(struct alarm *alarm, ktime_t now)
{
	cm_timer_set = false;
	return ALARMTIMER_NORESTART;
}
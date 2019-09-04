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
struct rtc_device {int pie_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ rtc_update_hrtimer (struct rtc_device*,int) ; 
 int /*<<< orphan*/  trace_rtc_irq_set_state (int,int) ; 

int rtc_irq_set_state(struct rtc_device *rtc, int enabled)
{
	int err = 0;

	while (rtc_update_hrtimer(rtc, enabled) < 0)
		cpu_relax();

	rtc->pie_enabled = enabled;

	trace_rtc_irq_set_state(enabled, err);
	return err;
}
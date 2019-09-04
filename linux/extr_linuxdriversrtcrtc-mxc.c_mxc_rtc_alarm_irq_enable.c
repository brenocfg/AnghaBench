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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_ALM_BIT ; 
 int /*<<< orphan*/  mxc_rtc_irq_enable (struct device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mxc_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	mxc_rtc_irq_enable(dev, RTC_ALM_BIT, enabled);
	return 0;
}
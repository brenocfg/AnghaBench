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
typedef  scalar_t__ u32 ;
struct xlnx_rtc_dev {scalar_t__ reg_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_INT_ALRM ; 
 scalar_t__ RTC_INT_DIS ; 
 scalar_t__ RTC_INT_EN ; 
 struct xlnx_rtc_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int xlnx_rtc_alarm_irq_enable(struct device *dev, u32 enabled)
{
	struct xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);

	if (enabled)
		writel(RTC_INT_ALRM, xrtcdev->reg_base + RTC_INT_EN);
	else
		writel(RTC_INT_ALRM, xrtcdev->reg_base + RTC_INT_DIS);

	return 0;
}
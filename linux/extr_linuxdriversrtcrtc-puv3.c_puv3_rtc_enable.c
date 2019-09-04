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
 int /*<<< orphan*/  RTC_RTSR ; 
 int RTC_RTSR_HZE ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void puv3_rtc_enable(struct device *dev, int en)
{
	if (!en) {
		writel(readl(RTC_RTSR) & ~RTC_RTSR_HZE, RTC_RTSR);
	} else {
		/* re-enable the device, and check it is ok */
		if ((readl(RTC_RTSR) & RTC_RTSR_HZE) == 0) {
			dev_info(dev, "rtc disabled, re-enabling\n");
			writel(readl(RTC_RTSR) | RTC_RTSR_HZE, RTC_RTSR);
		}
	}
}
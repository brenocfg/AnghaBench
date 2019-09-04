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
struct tegra_rtc_info {scalar_t__ rtc_base; } ;
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int TEGRA_RTC_INTR_STATUS_SEC_ALARM0 ; 
 scalar_t__ TEGRA_RTC_REG_INTR_STATUS ; 
 scalar_t__ TEGRA_RTC_REG_SECONDS_ALARM0 ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	unsigned long sec;
	unsigned tmp;

	sec = readl(info->rtc_base + TEGRA_RTC_REG_SECONDS_ALARM0);

	if (sec == 0) {
		/* alarm is disabled. */
		alarm->enabled = 0;
	} else {
		/* alarm is enabled. */
		alarm->enabled = 1;
		rtc_time_to_tm(sec, &alarm->time);
	}

	tmp = readl(info->rtc_base + TEGRA_RTC_REG_INTR_STATUS);
	alarm->pending = (tmp & TEGRA_RTC_INTR_STATUS_SEC_ALARM0) != 0;

	return 0;
}
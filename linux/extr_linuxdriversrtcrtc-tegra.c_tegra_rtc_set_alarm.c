#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_rtc_info {scalar_t__ rtc_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; } ;
struct rtc_wkalrm {TYPE_1__ time; scalar_t__ enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TEGRA_RTC_REG_SECONDS_ALARM0 ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_tm_to_time (TYPE_1__*,unsigned long*) ; 
 int /*<<< orphan*/  tegra_rtc_alarm_irq_enable (struct device*,int) ; 
 int /*<<< orphan*/  tegra_rtc_wait_while_busy (struct device*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int tegra_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	unsigned long sec;

	if (alarm->enabled)
		rtc_tm_to_time(&alarm->time, &sec);
	else
		sec = 0;

	tegra_rtc_wait_while_busy(dev);
	writel(sec, info->rtc_base + TEGRA_RTC_REG_SECONDS_ALARM0);
	dev_vdbg(dev, "alarm read back as %d\n",
		readl(info->rtc_base + TEGRA_RTC_REG_SECONDS_ALARM0));

	/* if successfully written and alarm is enabled ... */
	if (sec) {
		tegra_rtc_alarm_irq_enable(dev, 1);

		dev_vdbg(dev, "alarm set as %lu. %d/%d/%d %d:%02u:%02u\n",
			sec,
			alarm->time.tm_mon+1,
			alarm->time.tm_mday,
			alarm->time.tm_year+1900,
			alarm->time.tm_hour,
			alarm->time.tm_min,
			alarm->time.tm_sec);
	} else {
		/* disable alarm if 0 or write error. */
		dev_vdbg(dev, "alarm disabled\n");
		tegra_rtc_alarm_irq_enable(dev, 0);
	}

	return 0;
}
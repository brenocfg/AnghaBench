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
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TEGRA_RTC_REG_SECONDS ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int tegra_rtc_wait_while_busy (struct device*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int tegra_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	unsigned long sec;
	int ret;

	/* convert tm to seconds. */
	rtc_tm_to_time(tm, &sec);

	dev_vdbg(dev, "time set to %lu. %d/%d/%d %d:%02u:%02u\n",
		sec,
		tm->tm_mon+1,
		tm->tm_mday,
		tm->tm_year+1900,
		tm->tm_hour,
		tm->tm_min,
		tm->tm_sec
	);

	/* seconds only written if wait succeeded. */
	ret = tegra_rtc_wait_while_busy(dev);
	if (!ret)
		writel(sec, info->rtc_base + TEGRA_RTC_REG_SECONDS);

	dev_vdbg(dev, "time read back as %d\n",
		readl(info->rtc_base + TEGRA_RTC_REG_SECONDS));

	return ret;
}
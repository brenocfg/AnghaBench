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
struct tegra_rtc_info {int /*<<< orphan*/  tegra_rtc_lock; scalar_t__ rtc_base; } ;
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TEGRA_RTC_REG_MILLI_SECONDS ; 
 scalar_t__ TEGRA_RTC_REG_SHADOW_SECONDS ; 
 struct tegra_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,unsigned long,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tegra_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct tegra_rtc_info *info = dev_get_drvdata(dev);
	unsigned long sec, msec;
	unsigned long sl_irq_flags;

	/* RTC hardware copies seconds to shadow seconds when a read
	 * of milliseconds occurs. use a lock to keep other threads out. */
	spin_lock_irqsave(&info->tegra_rtc_lock, sl_irq_flags);

	msec = readl(info->rtc_base + TEGRA_RTC_REG_MILLI_SECONDS);
	sec = readl(info->rtc_base + TEGRA_RTC_REG_SHADOW_SECONDS);

	spin_unlock_irqrestore(&info->tegra_rtc_lock, sl_irq_flags);

	rtc_time_to_tm(sec, tm);

	dev_vdbg(dev, "time read as %lu. %d/%d/%d %d:%02u:%02u\n",
		sec,
		tm->tm_mon + 1,
		tm->tm_mday,
		tm->tm_year + 1900,
		tm->tm_hour,
		tm->tm_min,
		tm->tm_sec
	);

	return 0;
}
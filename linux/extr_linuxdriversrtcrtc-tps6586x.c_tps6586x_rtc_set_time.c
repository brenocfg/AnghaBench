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
typedef  unsigned long long u8 ;
typedef  scalar_t__ time64_t ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_COUNT4 ; 
 int /*<<< orphan*/  RTC_CTRL ; 
 int /*<<< orphan*/  RTC_ENABLE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 
 struct device* to_tps6586x_dev (struct device*) ; 
 int tps6586x_clr_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tps6586x_set_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tps6586x_writes (struct device*,int /*<<< orphan*/ ,int,unsigned long long*) ; 

__attribute__((used)) static int tps6586x_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct device *tps_dev = to_tps6586x_dev(dev);
	unsigned long long ticks;
	time64_t seconds;
	u8 buff[5];
	int ret;

	seconds = rtc_tm_to_time64(tm);

	ticks = (unsigned long long)seconds << 10;
	buff[0] = (ticks >> 32) & 0xff;
	buff[1] = (ticks >> 24) & 0xff;
	buff[2] = (ticks >> 16) & 0xff;
	buff[3] = (ticks >> 8) & 0xff;
	buff[4] = ticks & 0xff;

	/* Disable RTC before changing time */
	ret = tps6586x_clr_bits(tps_dev, RTC_CTRL, RTC_ENABLE);
	if (ret < 0) {
		dev_err(dev, "failed to clear RTC_ENABLE\n");
		return ret;
	}

	ret = tps6586x_writes(tps_dev, RTC_COUNT4, sizeof(buff), buff);
	if (ret < 0) {
		dev_err(dev, "failed to program new time\n");
		return ret;
	}

	/* Enable RTC */
	ret = tps6586x_set_bits(tps_dev, RTC_CTRL, RTC_ENABLE);
	if (ret < 0) {
		dev_err(dev, "failed to set RTC_ENABLE\n");
		return ret;
	}
	return 0;
}
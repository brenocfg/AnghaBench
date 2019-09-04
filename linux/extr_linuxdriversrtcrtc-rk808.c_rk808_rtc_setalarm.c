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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; int /*<<< orphan*/  tm_wday; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct rk808_rtc {struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int NUM_ALARM_REGS ; 
 int /*<<< orphan*/  RK808_ALARM_SECONDS_REG ; 
 int /*<<< orphan*/  bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rk808_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gregorian_to_rockchip (TYPE_1__*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int rk808_rtc_start_alarm (struct rk808_rtc*) ; 
 int rk808_rtc_stop_alarm (struct rk808_rtc*) ; 

__attribute__((used)) static int rk808_rtc_setalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rk808_rtc *rk808_rtc = dev_get_drvdata(dev);
	struct rk808 *rk808 = rk808_rtc->rk808;
	u8 alrm_data[NUM_ALARM_REGS];
	int ret;

	ret = rk808_rtc_stop_alarm(rk808_rtc);
	if (ret) {
		dev_err(dev, "Failed to stop alarm: %d\n", ret);
		return ret;
	}
	dev_dbg(dev, "alrm set RTC date/time %4d-%02d-%02d(%d) %02d:%02d:%02d\n",
		1900 + alrm->time.tm_year, alrm->time.tm_mon + 1,
		alrm->time.tm_mday, alrm->time.tm_wday, alrm->time.tm_hour,
		alrm->time.tm_min, alrm->time.tm_sec);

	gregorian_to_rockchip(&alrm->time);
	alrm_data[0] = bin2bcd(alrm->time.tm_sec);
	alrm_data[1] = bin2bcd(alrm->time.tm_min);
	alrm_data[2] = bin2bcd(alrm->time.tm_hour);
	alrm_data[3] = bin2bcd(alrm->time.tm_mday);
	alrm_data[4] = bin2bcd(alrm->time.tm_mon + 1);
	alrm_data[5] = bin2bcd(alrm->time.tm_year - 100);

	ret = regmap_bulk_write(rk808->regmap, RK808_ALARM_SECONDS_REG,
				alrm_data, NUM_ALARM_REGS);
	if (ret) {
		dev_err(dev, "Failed to bulk write: %d\n", ret);
		return ret;
	}
	if (alrm->enabled) {
		ret = rk808_rtc_start_alarm(rk808_rtc);
		if (ret) {
			dev_err(dev, "Failed to start alarm: %d\n", ret);
			return ret;
		}
	}
	return 0;
}
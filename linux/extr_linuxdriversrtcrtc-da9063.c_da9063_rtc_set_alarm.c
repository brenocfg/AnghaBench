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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
struct da9063_compatible_rtc_regmap {size_t rtc_data_start; int /*<<< orphan*/  rtc_alarm_len; int /*<<< orphan*/  rtc_alarm_secs_reg; } ;
struct da9063_compatible_rtc {int /*<<< orphan*/  alarm_time; int /*<<< orphan*/  regmap; struct da9063_compatible_rtc_regmap* config; } ;

/* Variables and functions */
 int RTC_DATA_LEN ; 
 int /*<<< orphan*/  da9063_data_to_tm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct da9063_compatible_rtc*) ; 
 int da9063_rtc_start_alarm (struct device*) ; 
 int da9063_rtc_stop_alarm (struct device*) ; 
 int /*<<< orphan*/  da9063_tm_to_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct da9063_compatible_rtc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct da9063_compatible_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9063_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	const struct da9063_compatible_rtc_regmap *config = rtc->config;
	u8 data[RTC_DATA_LEN];
	int ret;

	da9063_tm_to_data(&alrm->time, data, rtc);

	ret = da9063_rtc_stop_alarm(dev);
	if (ret < 0) {
		dev_err(dev, "Failed to stop alarm: %d\n", ret);
		return ret;
	}

	ret = regmap_bulk_write(rtc->regmap,
				config->rtc_alarm_secs_reg,
				&data[config->rtc_data_start],
				config->rtc_alarm_len);
	if (ret < 0) {
		dev_err(dev, "Failed to write alarm: %d\n", ret);
		return ret;
	}

	da9063_data_to_tm(data, &rtc->alarm_time, rtc);

	if (alrm->enabled) {
		ret = da9063_rtc_start_alarm(dev);
		if (ret < 0) {
			dev_err(dev, "Failed to start alarm: %d\n", ret);
			return ret;
		}
	}

	return ret;
}
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
typedef  int u32 ;
typedef  int /*<<< orphan*/  time64_t ;
struct sprd_rtc {int base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
typedef  enum sprd_rtc_reg_types { ____Placeholder_sprd_rtc_reg_types } sprd_rtc_reg_types ;

/* Variables and functions */
 int EINVAL ; 
#define  SPRD_RTC_ALARM 130 
 int SPRD_RTC_ALMTIME_INT_MASK ; 
#define  SPRD_RTC_AUX_ALARM 129 
 int SPRD_RTC_DAY_ALM_UPD ; 
 int SPRD_RTC_DAY_AUXALM_UPD ; 
 int SPRD_RTC_DAY_CNT_UPD ; 
 int SPRD_RTC_HOUR_ALM_UPD ; 
 int SPRD_RTC_HOUR_AUXALM_UPD ; 
 int SPRD_RTC_HOUR_CNT_UPD ; 
 int SPRD_RTC_INT_CLR ; 
 int SPRD_RTC_INT_RAW_STS ; 
 int SPRD_RTC_MIN_ALM_UPD ; 
 int SPRD_RTC_MIN_AUXALM_UPD ; 
 int SPRD_RTC_MIN_CNT_UPD ; 
 int /*<<< orphan*/  SPRD_RTC_POLL_DELAY_US ; 
 int /*<<< orphan*/  SPRD_RTC_POLL_TIMEOUT ; 
 int SPRD_RTC_SEC_ALM_UPD ; 
 int SPRD_RTC_SEC_AUXALM_UPD ; 
 int SPRD_RTC_SEC_CNT_UPD ; 
#define  SPRD_RTC_TIME 128 
 int SPRD_RTC_TIME_INT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int div_s64_rem (int /*<<< orphan*/ ,int,int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sprd_rtc_set_secs(struct sprd_rtc *rtc, enum sprd_rtc_reg_types type,
			     time64_t secs)
{
	u32 sec_reg, min_reg, hour_reg, day_reg, sts_mask;
	u32 sec, min, hour, day, val;
	int ret, rem;

	/* convert seconds to RTC time format */
	day = div_s64_rem(secs, 86400, &rem);
	hour = rem / 3600;
	rem -= hour * 3600;
	min = rem / 60;
	sec = rem - min * 60;

	switch (type) {
	case SPRD_RTC_TIME:
		sec_reg = SPRD_RTC_SEC_CNT_UPD;
		min_reg = SPRD_RTC_MIN_CNT_UPD;
		hour_reg = SPRD_RTC_HOUR_CNT_UPD;
		day_reg = SPRD_RTC_DAY_CNT_UPD;
		sts_mask = SPRD_RTC_TIME_INT_MASK;
		break;
	case SPRD_RTC_ALARM:
		sec_reg = SPRD_RTC_SEC_ALM_UPD;
		min_reg = SPRD_RTC_MIN_ALM_UPD;
		hour_reg = SPRD_RTC_HOUR_ALM_UPD;
		day_reg = SPRD_RTC_DAY_ALM_UPD;
		sts_mask = SPRD_RTC_ALMTIME_INT_MASK;
		break;
	case SPRD_RTC_AUX_ALARM:
		sec_reg = SPRD_RTC_SEC_AUXALM_UPD;
		min_reg = SPRD_RTC_MIN_AUXALM_UPD;
		hour_reg = SPRD_RTC_HOUR_AUXALM_UPD;
		day_reg = SPRD_RTC_DAY_AUXALM_UPD;
		sts_mask = 0;
		break;
	default:
		return -EINVAL;
	}

	ret = regmap_write(rtc->regmap, rtc->base + sec_reg, sec);
	if (ret)
		return ret;

	ret = regmap_write(rtc->regmap, rtc->base + min_reg, min);
	if (ret)
		return ret;

	ret = regmap_write(rtc->regmap, rtc->base + hour_reg, hour);
	if (ret)
		return ret;

	ret = regmap_write(rtc->regmap, rtc->base + day_reg, day);
	if (ret)
		return ret;

	if (type == SPRD_RTC_AUX_ALARM)
		return 0;

	/*
	 * Since the time and normal alarm registers are put in always-power-on
	 * region supplied by VDDRTC, then these registers changing time will
	 * be very long, about 125ms. Thus here we should wait until all
	 * values are updated successfully.
	 */
	ret = regmap_read_poll_timeout(rtc->regmap,
				       rtc->base + SPRD_RTC_INT_RAW_STS, val,
				       ((val & sts_mask) == sts_mask),
				       SPRD_RTC_POLL_DELAY_US,
				       SPRD_RTC_POLL_TIMEOUT);
	if (ret < 0) {
		dev_err(rtc->dev, "set time/alarm values timeout\n");
		return ret;
	}

	return regmap_write(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			    sts_mask);
}
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
typedef  scalar_t__ u16 ;
struct rtc_time {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; struct rtc_time time; } ;
struct mt6397_rtc {int /*<<< orphan*/  lock; scalar_t__ addr_base; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_AL_MASK ; 
 int /*<<< orphan*/  RTC_AL_MASK_DOW ; 
 scalar_t__ RTC_AL_SEC ; 
 scalar_t__ RTC_IRQ_EN ; 
 int /*<<< orphan*/  RTC_IRQ_EN_ONESHOT_AL ; 
 scalar_t__ RTC_MIN_YEAR_OFFSET ; 
 int RTC_OFFSET_COUNT ; 
 size_t RTC_OFFSET_DOM ; 
 size_t RTC_OFFSET_HOUR ; 
 size_t RTC_OFFSET_MIN ; 
 size_t RTC_OFFSET_MTH ; 
 size_t RTC_OFFSET_SEC ; 
 size_t RTC_OFFSET_YEAR ; 
 struct mt6397_rtc* dev_get_drvdata (struct device*) ; 
 int mtk_rtc_write_trigger (struct mt6397_rtc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct rtc_time *tm = &alm->time;
	struct mt6397_rtc *rtc = dev_get_drvdata(dev);
	int ret;
	u16 data[RTC_OFFSET_COUNT];

	tm->tm_year -= RTC_MIN_YEAR_OFFSET;
	tm->tm_mon++;

	data[RTC_OFFSET_SEC] = tm->tm_sec;
	data[RTC_OFFSET_MIN] = tm->tm_min;
	data[RTC_OFFSET_HOUR] = tm->tm_hour;
	data[RTC_OFFSET_DOM] = tm->tm_mday;
	data[RTC_OFFSET_MTH] = tm->tm_mon;
	data[RTC_OFFSET_YEAR] = tm->tm_year;

	mutex_lock(&rtc->lock);
	if (alm->enabled) {
		ret = regmap_bulk_write(rtc->regmap,
					rtc->addr_base + RTC_AL_SEC,
					data, RTC_OFFSET_COUNT);
		if (ret < 0)
			goto exit;
		ret = regmap_write(rtc->regmap, rtc->addr_base + RTC_AL_MASK,
				   RTC_AL_MASK_DOW);
		if (ret < 0)
			goto exit;
		ret = regmap_update_bits(rtc->regmap,
					 rtc->addr_base + RTC_IRQ_EN,
					 RTC_IRQ_EN_ONESHOT_AL,
					 RTC_IRQ_EN_ONESHOT_AL);
		if (ret < 0)
			goto exit;
	} else {
		ret = regmap_update_bits(rtc->regmap,
					 rtc->addr_base + RTC_IRQ_EN,
					 RTC_IRQ_EN_ONESHOT_AL, 0);
		if (ret < 0)
			goto exit;
	}

	/* All alarm time register write to hardware after calling
	 * mtk_rtc_write_trigger. This can avoid race condition if alarm
	 * occur happen during writing alarm time register.
	 */
	ret = mtk_rtc_write_trigger(rtc);
exit:
	mutex_unlock(&rtc->lock);
	return ret;
}
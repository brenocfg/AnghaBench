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
struct TYPE_2__ {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; TYPE_1__ time; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int RTC_YEAR_OFFSET ; 
 int /*<<< orphan*/  TPS80031_ALARM_SECONDS_REG ; 
 int TPS80031_RTC_ALARM_NUM_REGS ; 
 int /*<<< orphan*/  TPS80031_SLAVE_ID1 ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int tps80031_rtc_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 
 int tps80031_writes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tps80031_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	u8 buff[TPS80031_RTC_ALARM_NUM_REGS];
	int ret;

	buff[0] = bin2bcd(alrm->time.tm_sec);
	buff[1] = bin2bcd(alrm->time.tm_min);
	buff[2] = bin2bcd(alrm->time.tm_hour);
	buff[3] = bin2bcd(alrm->time.tm_mday);
	buff[4] = bin2bcd(alrm->time.tm_mon + 1);
	buff[5] = bin2bcd(alrm->time.tm_year % RTC_YEAR_OFFSET);
	ret = tps80031_writes(dev->parent, TPS80031_SLAVE_ID1,
			TPS80031_ALARM_SECONDS_REG,
			TPS80031_RTC_ALARM_NUM_REGS, buff);
	if (ret < 0) {
		dev_err(dev, "Writing RTC_ALARM failed, err %d\n", ret);
		return ret;
	}
	return tps80031_rtc_alarm_irq_enable(dev, alrm->enabled);
}
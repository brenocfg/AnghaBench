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
typedef  int u32 ;
struct vt8500_rtc {scalar_t__ regbase; } ;
struct TYPE_2__ {void* tm_sec; void* tm_min; void* tm_hour; void* tm_mday; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALARM_DAY_MASK ; 
 int ALARM_DAY_S ; 
 int ALARM_ENABLE_MASK ; 
 int TIME_HOUR_MASK ; 
 int TIME_HOUR_S ; 
 int TIME_MIN_MASK ; 
 int TIME_MIN_S ; 
 int TIME_SEC_MASK ; 
 scalar_t__ VT8500_RTC_AS ; 
 scalar_t__ VT8500_RTC_IS ; 
 int VT8500_RTC_IS_ALARM ; 
 void* bcd2bin (int) ; 
 struct vt8500_rtc* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int rtc_valid_tm (TYPE_1__*) ; 

__attribute__((used)) static int vt8500_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);
	u32 isr, alarm;

	alarm = readl(vt8500_rtc->regbase + VT8500_RTC_AS);
	isr = readl(vt8500_rtc->regbase + VT8500_RTC_IS);

	alrm->time.tm_mday = bcd2bin((alarm & ALARM_DAY_MASK) >> ALARM_DAY_S);
	alrm->time.tm_hour = bcd2bin((alarm & TIME_HOUR_MASK) >> TIME_HOUR_S);
	alrm->time.tm_min = bcd2bin((alarm & TIME_MIN_MASK) >> TIME_MIN_S);
	alrm->time.tm_sec = bcd2bin((alarm & TIME_SEC_MASK));

	alrm->enabled = (alarm & ALARM_ENABLE_MASK) ? 1 : 0;
	alrm->pending = (isr & VT8500_RTC_IS_ALARM) ? 1 : 0;

	return rtc_valid_tm(&alrm->time);
}
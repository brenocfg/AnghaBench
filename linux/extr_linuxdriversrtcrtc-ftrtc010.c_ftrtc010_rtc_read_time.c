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
typedef  int timeu64_t ;
struct rtc_time {int dummy; } ;
struct ftrtc010_rtc {scalar_t__ rtc_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ FTRTC010_RTC_DAYS ; 
 scalar_t__ FTRTC010_RTC_HOUR ; 
 scalar_t__ FTRTC010_RTC_MINUTE ; 
 scalar_t__ FTRTC010_RTC_RECORD ; 
 scalar_t__ FTRTC010_RTC_SECOND ; 
 struct ftrtc010_rtc* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,struct rtc_time*) ; 

__attribute__((used)) static int ftrtc010_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct ftrtc010_rtc *rtc = dev_get_drvdata(dev);

	u32 days, hour, min, sec, offset;
	timeu64_t time;

	sec  = readl(rtc->rtc_base + FTRTC010_RTC_SECOND);
	min  = readl(rtc->rtc_base + FTRTC010_RTC_MINUTE);
	hour = readl(rtc->rtc_base + FTRTC010_RTC_HOUR);
	days = readl(rtc->rtc_base + FTRTC010_RTC_DAYS);
	offset = readl(rtc->rtc_base + FTRTC010_RTC_RECORD);

	time = offset + days * 86400 + hour * 3600 + min * 60 + sec;

	rtc_time64_to_tm(time, tm);

	return 0;
}
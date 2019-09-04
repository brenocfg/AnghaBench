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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct dc_rtc {int dummy; } ;

/* Variables and functions */
 int dc_rtc_read (struct dc_rtc*,unsigned long*) ; 
 struct dc_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static int dc_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct dc_rtc *rtc = dev_get_drvdata(dev);
	unsigned long now;
	int ret;

	ret = dc_rtc_read(rtc, &now);
	if (ret < 0)
		return ret;
	rtc_time64_to_tm(now, tm);

	return 0;
}
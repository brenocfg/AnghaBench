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
typedef  scalar_t__ u32 ;
struct sam9_rtc {int dummy; } ;
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; scalar_t__ tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EILSEQ ; 
 int /*<<< orphan*/  VR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sam9_rtc* dev_get_drvdata (struct device*) ; 
 scalar_t__ gpbr_readl (struct sam9_rtc*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (scalar_t__,struct rtc_time*) ; 
 scalar_t__ rtt_readl (struct sam9_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_rtc_readtime(struct device *dev, struct rtc_time *tm)
{
	struct sam9_rtc *rtc = dev_get_drvdata(dev);
	u32 secs, secs2;
	u32 offset;

	/* read current time offset */
	offset = gpbr_readl(rtc);
	if (offset == 0)
		return -EILSEQ;

	/* reread the counter to help sync the two clock domains */
	secs = rtt_readl(rtc, VR);
	secs2 = rtt_readl(rtc, VR);
	if (secs != secs2)
		secs = rtt_readl(rtc, VR);

	rtc_time_to_tm(offset + secs, tm);

	dev_dbg(dev, "%s: %4d-%02d-%02d %02d:%02d:%02d\n", "readtime",
		1900 + tm->tm_year, tm->tm_mon, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);

	return 0;
}
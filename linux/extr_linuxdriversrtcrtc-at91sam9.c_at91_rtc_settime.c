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
typedef  unsigned long u32 ;
struct sam9_rtc {int dummy; } ;
struct rtc_time {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; scalar_t__ tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long ALARM_DISABLED ; 
 int /*<<< orphan*/  AR ; 
 unsigned long AT91_RTT_ALMIEN ; 
 unsigned long AT91_RTT_RTTINCIEN ; 
 unsigned long AT91_RTT_RTTRST ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sam9_rtc* dev_get_drvdata (struct device*) ; 
 unsigned long gpbr_readl (struct sam9_rtc*) ; 
 int /*<<< orphan*/  gpbr_writel (struct sam9_rtc*,unsigned long) ; 
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 unsigned long rtt_readl (struct sam9_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtt_writel (struct sam9_rtc*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int at91_rtc_settime(struct device *dev, struct rtc_time *tm)
{
	struct sam9_rtc *rtc = dev_get_drvdata(dev);
	int err;
	u32 offset, alarm, mr;
	unsigned long secs;

	dev_dbg(dev, "%s: %4d-%02d-%02d %02d:%02d:%02d\n", "settime",
		1900 + tm->tm_year, tm->tm_mon, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);

	err = rtc_tm_to_time(tm, &secs);
	if (err != 0)
		return err;

	mr = rtt_readl(rtc, MR);

	/* disable interrupts */
	rtt_writel(rtc, MR, mr & ~(AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN));

	/* read current time offset */
	offset = gpbr_readl(rtc);

	/* store the new base time in a battery backup register */
	secs += 1;
	gpbr_writel(rtc, secs);

	/* adjust the alarm time for the new base */
	alarm = rtt_readl(rtc, AR);
	if (alarm != ALARM_DISABLED) {
		if (offset > secs) {
			/* time jumped backwards, increase time until alarm */
			alarm += (offset - secs);
		} else if ((alarm + offset) > secs) {
			/* time jumped forwards, decrease time until alarm */
			alarm -= (secs - offset);
		} else {
			/* time jumped past the alarm, disable alarm */
			alarm = ALARM_DISABLED;
			mr &= ~AT91_RTT_ALMIEN;
		}
		rtt_writel(rtc, AR, alarm);
	}

	/* reset the timer, and re-enable interrupts */
	rtt_writel(rtc, MR, mr | AT91_RTT_RTTRST);

	return 0;
}
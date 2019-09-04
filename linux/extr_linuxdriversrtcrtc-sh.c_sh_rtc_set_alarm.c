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
struct sh_rtc {int /*<<< orphan*/  lock; scalar_t__ regbase; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; } ;
struct rtc_wkalrm {scalar_t__ enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RCR1 ; 
 unsigned int RCR1_AF ; 
 unsigned int RCR1_AIE ; 
 int /*<<< orphan*/  RDAYAR ; 
 int /*<<< orphan*/  RHRAR ; 
 int /*<<< orphan*/  RMINAR ; 
 int /*<<< orphan*/  RMONAR ; 
 int /*<<< orphan*/  RSECAR ; 
 int /*<<< orphan*/  RWKAR ; 
 struct sh_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  sh_rtc_write_alarm_value (struct sh_rtc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int sh_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct sh_rtc *rtc = dev_get_drvdata(dev);
	unsigned int rcr1;
	struct rtc_time *tm = &wkalrm->time;
	int mon;

	spin_lock_irq(&rtc->lock);

	/* disable alarm interrupt and clear the alarm flag */
	rcr1 = readb(rtc->regbase + RCR1);
	rcr1 &= ~(RCR1_AF | RCR1_AIE);
	writeb(rcr1, rtc->regbase + RCR1);

	/* set alarm time */
	sh_rtc_write_alarm_value(rtc, tm->tm_sec,  RSECAR);
	sh_rtc_write_alarm_value(rtc, tm->tm_min,  RMINAR);
	sh_rtc_write_alarm_value(rtc, tm->tm_hour, RHRAR);
	sh_rtc_write_alarm_value(rtc, tm->tm_wday, RWKAR);
	sh_rtc_write_alarm_value(rtc, tm->tm_mday, RDAYAR);
	mon = tm->tm_mon;
	if (mon >= 0)
		mon += 1;
	sh_rtc_write_alarm_value(rtc, mon, RMONAR);

	if (wkalrm->enabled) {
		rcr1 |= RCR1_AIE;
		writeb(rcr1, rtc->regbase + RCR1);
	}

	spin_unlock_irq(&rtc->lock);

	return 0;
}
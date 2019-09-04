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
typedef  int u8 ;
struct device {int dummy; } ;
struct davinci_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRTCSS_RTC_CCTRL ; 
 int PRTCSS_RTC_CCTRL_AIEN ; 
 int PRTCSS_RTC_CCTRL_ALMFLG ; 
 int PRTCSS_RTC_CCTRL_DAEN ; 
 int PRTCSS_RTC_CCTRL_HAEN ; 
 int PRTCSS_RTC_CCTRL_MAEN ; 
 int /*<<< orphan*/  davinci_rtc_lock ; 
 int /*<<< orphan*/  davinci_rtcss_calendar_wait (struct davinci_rtc*) ; 
 struct davinci_rtc* dev_get_drvdata (struct device*) ; 
 int rtcss_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcss_write (struct davinci_rtc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int davinci_rtc_alarm_irq_enable(struct device *dev,
					unsigned int enabled)
{
	struct davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	unsigned long flags;
	u8 rtc_cctrl = rtcss_read(davinci_rtc, PRTCSS_RTC_CCTRL);

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	if (enabled)
		rtc_cctrl |= PRTCSS_RTC_CCTRL_DAEN |
			     PRTCSS_RTC_CCTRL_HAEN |
			     PRTCSS_RTC_CCTRL_MAEN |
			     PRTCSS_RTC_CCTRL_ALMFLG |
			     PRTCSS_RTC_CCTRL_AIEN;
	else
		rtc_cctrl &= ~PRTCSS_RTC_CCTRL_AIEN;

	davinci_rtcss_calendar_wait(davinci_rtc);
	rtcss_write(davinci_rtc, rtc_cctrl, PRTCSS_RTC_CCTRL);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	return 0;
}
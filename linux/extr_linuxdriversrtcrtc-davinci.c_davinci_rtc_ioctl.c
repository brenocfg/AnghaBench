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
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  PRTCSS_RTC_CTRL ; 
 int PRTCSS_RTC_CTRL_WDTFLG ; 
 int PRTCSS_RTC_CTRL_WEN ; 
#define  RTC_WIE_OFF 129 
#define  RTC_WIE_ON 128 
 int /*<<< orphan*/  davinci_rtc_lock ; 
 struct davinci_rtc* dev_get_drvdata (struct device*) ; 
 int rtcss_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcss_write (struct davinci_rtc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
davinci_rtc_ioctl(struct device *dev, unsigned int cmd, unsigned long arg)
{
	struct davinci_rtc *davinci_rtc = dev_get_drvdata(dev);
	u8 rtc_ctrl;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&davinci_rtc_lock, flags);

	rtc_ctrl = rtcss_read(davinci_rtc, PRTCSS_RTC_CTRL);

	switch (cmd) {
	case RTC_WIE_ON:
		rtc_ctrl |= PRTCSS_RTC_CTRL_WEN | PRTCSS_RTC_CTRL_WDTFLG;
		break;
	case RTC_WIE_OFF:
		rtc_ctrl &= ~PRTCSS_RTC_CTRL_WEN;
		break;
	default:
		ret = -ENOIOCTLCMD;
	}

	rtcss_write(davinci_rtc, rtc_ctrl, PRTCSS_RTC_CTRL);

	spin_unlock_irqrestore(&davinci_rtc_lock, flags);

	return ret;
}
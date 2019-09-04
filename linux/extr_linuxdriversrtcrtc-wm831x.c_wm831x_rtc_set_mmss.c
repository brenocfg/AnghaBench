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
struct wm831x_rtc {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  WM831X_RTC_CONTROL ; 
 int WM831X_RTC_SYNC_BUSY ; 
 int /*<<< orphan*/  WM831X_RTC_TIME_1 ; 
 int /*<<< orphan*/  WM831X_RTC_TIME_2 ; 
 int WM831X_SET_TIME_RETRIES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct wm831x_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,unsigned long) ; 
 int wm831x_rtc_readtime (struct device*,struct rtc_time*) ; 

__attribute__((used)) static int wm831x_rtc_set_mmss(struct device *dev, unsigned long time)
{
	struct wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	struct wm831x *wm831x = wm831x_rtc->wm831x;
	struct rtc_time new_tm;
	unsigned long new_time;
	int ret;
	int count = 0;

	ret = wm831x_reg_write(wm831x, WM831X_RTC_TIME_1,
			       (time >> 16) & 0xffff);
	if (ret < 0) {
		dev_err(dev, "Failed to write TIME_1: %d\n", ret);
		return ret;
	}

	ret = wm831x_reg_write(wm831x, WM831X_RTC_TIME_2, time & 0xffff);
	if (ret < 0) {
		dev_err(dev, "Failed to write TIME_2: %d\n", ret);
		return ret;
	}

	/* Wait for the update to complete - should happen first time
	 * round but be conservative.
	 */
	do {
		msleep(1);

		ret = wm831x_reg_read(wm831x, WM831X_RTC_CONTROL);
		if (ret < 0)
			ret = WM831X_RTC_SYNC_BUSY;
	} while (!(ret & WM831X_RTC_SYNC_BUSY) &&
		 ++count < WM831X_SET_TIME_RETRIES);

	if (ret & WM831X_RTC_SYNC_BUSY) {
		dev_err(dev, "Timed out writing RTC update\n");
		return -EIO;
	}

	/* Check that the update was accepted; security features may
	 * have caused the update to be ignored.
	 */
	ret = wm831x_rtc_readtime(dev, &new_tm);
	if (ret < 0)
		return ret;

	ret = rtc_tm_to_time(&new_tm, &new_time);
	if (ret < 0) {
		dev_err(dev, "Failed to convert time: %d\n", ret);
		return ret;
	}

	/* Allow a second of change in case of tick */
	if (new_time - time > 1) {
		dev_err(dev, "RTC update not permitted by hardware\n");
		return -EPERM;
	}

	return 0;
}
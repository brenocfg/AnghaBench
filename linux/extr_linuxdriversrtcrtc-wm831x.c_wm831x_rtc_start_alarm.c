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
struct wm831x_rtc {int alarm_enabled; int /*<<< orphan*/  wm831x; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_RTC_ALM_ENA ; 
 int /*<<< orphan*/  WM831X_RTC_CONTROL ; 
 int wm831x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_rtc_start_alarm(struct wm831x_rtc *wm831x_rtc)
{
	wm831x_rtc->alarm_enabled = 1;

	return wm831x_set_bits(wm831x_rtc->wm831x, WM831X_RTC_CONTROL,
			       WM831X_RTC_ALM_ENA, WM831X_RTC_ALM_ENA);
}
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
struct TYPE_2__ {struct rtc_device* rtc; } ;
struct wm8350 {TYPE_1__ rtc; } ;
struct rtc_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_IRQF ; 
 int RTC_UF ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int) ; 

__attribute__((used)) static irqreturn_t wm8350_rtc_update_handler(int irq, void *data)
{
	struct wm8350 *wm8350 = data;
	struct rtc_device *rtc = wm8350->rtc.rtc;

	rtc_update_irq(rtc, 1, RTC_IRQF | RTC_UF);

	return IRQ_HANDLED;
}
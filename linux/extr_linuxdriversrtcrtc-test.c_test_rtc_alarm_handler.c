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
struct timer_list {int dummy; } ;
struct rtc_test_data {int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  alarm ; 
 struct rtc_test_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 struct rtc_test_data* rtd ; 

__attribute__((used)) static void test_rtc_alarm_handler(struct timer_list *t)
{
	struct rtc_test_data *rtd = from_timer(rtd, t, alarm);

	rtc_update_irq(rtd->rtc, 1, RTC_AF | RTC_IRQF);
}
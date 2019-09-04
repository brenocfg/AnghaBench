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
struct st_rtc {int /*<<< orphan*/  rtc_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RTC_AF ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t st_rtc_handler(int this_irq, void *data)
{
	struct st_rtc *rtc = (struct st_rtc *)data;

	rtc_update_irq(rtc->rtc_dev, 1, RTC_AF);

	return IRQ_HANDLED;
}
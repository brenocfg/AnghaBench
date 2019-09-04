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
struct rtc_device {int dummy; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RTCINTREG ; 
 int /*<<< orphan*/  RTCL1HREG ; 
 int /*<<< orphan*/  RTCL1LREG ; 
 int /*<<< orphan*/  RTCLONG1_INT ; 
 int /*<<< orphan*/  RTC_PF ; 
 unsigned long periodic_count ; 
 struct rtc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc1_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rtc2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rtclong1_interrupt(int irq, void *dev_id)
{
	struct platform_device *pdev = (struct platform_device *)dev_id;
	struct rtc_device *rtc = platform_get_drvdata(pdev);
	unsigned long count = periodic_count;

	rtc2_write(RTCINTREG, RTCLONG1_INT);

	rtc1_write(RTCL1LREG, count);
	rtc1_write(RTCL1HREG, count >> 16);

	rtc_update_irq(rtc, 1, RTC_PF);

	return IRQ_HANDLED;
}
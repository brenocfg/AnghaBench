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
struct pm860x_rtc_info {int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ALARM ; 
 int ALARM_EN ; 
 int ALARM_WAKEUP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PM8607_RTC1 ; 
 int /*<<< orphan*/  RTC_AF ; 
 int /*<<< orphan*/  pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rtc_update_handler(int irq, void *data)
{
	struct pm860x_rtc_info *info = (struct pm860x_rtc_info *)data;
	int mask;

	mask = ALARM | ALARM_WAKEUP;
	pm860x_set_bits(info->i2c, PM8607_RTC1, mask | ALARM_EN, mask);
	rtc_update_irq(info->rtc_dev, 1, RTC_AF);
	return IRQ_HANDLED;
}
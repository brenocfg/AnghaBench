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
struct max8907_rtc {int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MAX8907_REG_ALARM0_CNTL ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t max8907_irq_handler(int irq, void *data)
{
	struct max8907_rtc *rtc = data;

	regmap_write(rtc->regmap, MAX8907_REG_ALARM0_CNTL, 0);

	rtc_update_irq(rtc->rtc_dev, 1, RTC_IRQF | RTC_AF);

	return IRQ_HANDLED;
}
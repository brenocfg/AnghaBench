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
struct da9063_compatible_rtc_regmap {int /*<<< orphan*/  rtc_alarm_on_mask; int /*<<< orphan*/  rtc_alarm_year_reg; } ;
struct da9063_compatible_rtc {int rtc_sync; int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  regmap; struct da9063_compatible_rtc_regmap* config; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t da9063_alarm_event(int irq, void *data)
{
	struct da9063_compatible_rtc *rtc = data;
	const struct da9063_compatible_rtc_regmap *config = rtc->config;

	regmap_update_bits(rtc->regmap,
			   config->rtc_alarm_year_reg,
			   config->rtc_alarm_on_mask,
			   0);

	rtc->rtc_sync = true;
	rtc_update_irq(rtc->rtc_dev, 1, RTC_IRQF | RTC_AF);

	return IRQ_HANDLED;
}
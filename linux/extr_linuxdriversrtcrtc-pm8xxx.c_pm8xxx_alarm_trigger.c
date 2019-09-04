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
struct pm8xxx_rtc_regs {unsigned int alarm_en; int /*<<< orphan*/  alarm_ctrl2; int /*<<< orphan*/  alarm_ctrl; } ;
struct pm8xxx_rtc {int /*<<< orphan*/  rtc_dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ctrl_reg_lock; int /*<<< orphan*/  rtc; struct pm8xxx_rtc_regs* regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int PM8xxx_RTC_ALARM_CLEAR ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t pm8xxx_alarm_trigger(int irq, void *dev_id)
{
	struct pm8xxx_rtc *rtc_dd = dev_id;
	const struct pm8xxx_rtc_regs *regs = rtc_dd->regs;
	unsigned int ctrl_reg;
	int rc;
	unsigned long irq_flags;

	rtc_update_irq(rtc_dd->rtc, 1, RTC_IRQF | RTC_AF);

	spin_lock_irqsave(&rtc_dd->ctrl_reg_lock, irq_flags);

	/* Clear the alarm enable bit */
	rc = regmap_read(rtc_dd->regmap, regs->alarm_ctrl, &ctrl_reg);
	if (rc) {
		spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);
		goto rtc_alarm_handled;
	}

	ctrl_reg &= ~regs->alarm_en;

	rc = regmap_write(rtc_dd->regmap, regs->alarm_ctrl, ctrl_reg);
	if (rc) {
		spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);
		dev_err(rtc_dd->rtc_dev,
			"Write to alarm control register failed\n");
		goto rtc_alarm_handled;
	}

	spin_unlock_irqrestore(&rtc_dd->ctrl_reg_lock, irq_flags);

	/* Clear RTC alarm register */
	rc = regmap_read(rtc_dd->regmap, regs->alarm_ctrl2, &ctrl_reg);
	if (rc) {
		dev_err(rtc_dd->rtc_dev,
			"RTC Alarm control2 register read failed\n");
		goto rtc_alarm_handled;
	}

	ctrl_reg |= PM8xxx_RTC_ALARM_CLEAR;
	rc = regmap_write(rtc_dd->regmap, regs->alarm_ctrl2, ctrl_reg);
	if (rc)
		dev_err(rtc_dd->rtc_dev,
			"Write to RTC Alarm control2 register failed\n");

rtc_alarm_handled:
	return IRQ_HANDLED;
}
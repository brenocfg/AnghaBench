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
struct mutex {int dummy; } ;
struct ds3232 {TYPE_1__* rtc; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct mutex ops_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3232_REG_CR ; 
 int DS3232_REG_CR_A1IE ; 
 int /*<<< orphan*/  DS3232_REG_SR ; 
 int DS3232_REG_SR_A1F ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 struct ds3232* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_update_irq (TYPE_1__*,int,int) ; 

__attribute__((used)) static irqreturn_t ds3232_irq(int irq, void *dev_id)
{
	struct device *dev = dev_id;
	struct ds3232 *ds3232 = dev_get_drvdata(dev);
	struct mutex *lock = &ds3232->rtc->ops_lock;
	int ret;
	int stat, control;

	mutex_lock(lock);

	ret = regmap_read(ds3232->regmap, DS3232_REG_SR, &stat);
	if (ret)
		goto unlock;

	if (stat & DS3232_REG_SR_A1F) {
		ret = regmap_read(ds3232->regmap, DS3232_REG_CR, &control);
		if (ret) {
			dev_warn(ds3232->dev,
				 "Read Control Register error %d\n", ret);
		} else {
			/* disable alarm1 interrupt */
			control &= ~(DS3232_REG_CR_A1IE);
			ret = regmap_write(ds3232->regmap, DS3232_REG_CR,
					   control);
			if (ret) {
				dev_warn(ds3232->dev,
					 "Write Control Register error %d\n",
					 ret);
				goto unlock;
			}

			/* clear the alarm pend flag */
			stat &= ~DS3232_REG_SR_A1F;
			ret = regmap_write(ds3232->regmap, DS3232_REG_SR, stat);
			if (ret) {
				dev_warn(ds3232->dev,
					 "Write Status Register error %d\n",
					 ret);
				goto unlock;
			}

			rtc_update_irq(ds3232->rtc, 1, RTC_AF | RTC_IRQF);
		}
	}

unlock:
	mutex_unlock(lock);

	return IRQ_HANDLED;
}
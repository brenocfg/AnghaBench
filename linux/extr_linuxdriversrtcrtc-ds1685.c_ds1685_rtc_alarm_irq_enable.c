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
struct ds1685_priv {int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  (* write ) (struct ds1685_priv*,int /*<<< orphan*/ ,int) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CTRL_B ; 
 int RTC_CTRL_B_AIE ; 
 int /*<<< orphan*/  RTC_CTRL_C ; 
 struct ds1685_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub4 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub5 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1685_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct ds1685_priv *rtc = dev_get_drvdata(dev);
	unsigned long flags = 0;

	/* Enable/disable the Alarm IRQ-Enable flag. */
	spin_lock_irqsave(&rtc->lock, flags);

	/* Flip the requisite interrupt-enable bit. */
	if (enabled)
		rtc->write(rtc, RTC_CTRL_B, (rtc->read(rtc, RTC_CTRL_B) |
					     RTC_CTRL_B_AIE));
	else
		rtc->write(rtc, RTC_CTRL_B, (rtc->read(rtc, RTC_CTRL_B) &
					     ~(RTC_CTRL_B_AIE)));

	/* Read Control C to clear all the flag bits. */
	rtc->read(rtc, RTC_CTRL_C);
	spin_unlock_irqrestore(&rtc->lock, flags);

	return 0;
}
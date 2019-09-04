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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct armada38x_rtc {int /*<<< orphan*/  lock; TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  alarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALARM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_IRQ1_CONF ; 
 int /*<<< orphan*/  RTC_IRQ_AL_EN ; 
 struct armada38x_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_delayed_write (int /*<<< orphan*/ ,struct armada38x_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int armada38x_rtc_alarm_irq_enable(struct device *dev,
					 unsigned int enabled)
{
	struct armada38x_rtc *rtc = dev_get_drvdata(dev);
	u32 reg_irq = ALARM_REG(RTC_IRQ1_CONF, rtc->data->alarm);
	unsigned long flags;

	spin_lock_irqsave(&rtc->lock, flags);

	if (enabled)
		rtc_delayed_write(RTC_IRQ_AL_EN, rtc, reg_irq);
	else
		rtc_delayed_write(0, rtc, reg_irq);

	spin_unlock_irqrestore(&rtc->lock, flags);

	return 0;
}
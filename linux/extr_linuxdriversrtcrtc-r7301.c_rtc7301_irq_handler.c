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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {TYPE_1__ dev; } ;
struct rtc7301_priv {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RTC7301_ALARM_CONTROL ; 
 int RTC7301_ALARM_CONTROL_AF ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 struct rtc7301_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc7301_alarm_irq (struct rtc7301_priv*,int) ; 
 int rtc7301_read (struct rtc7301_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc7301_select_bank (struct rtc7301_priv*,int) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t rtc7301_irq_handler(int irq, void *dev_id)
{
	struct rtc_device *rtc = dev_id;
	struct rtc7301_priv *priv = dev_get_drvdata(rtc->dev.parent);
	unsigned long flags;
	irqreturn_t ret = IRQ_NONE;
	u8 alrm_ctrl;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 1);

	alrm_ctrl = rtc7301_read(priv, RTC7301_ALARM_CONTROL);
	if (alrm_ctrl & RTC7301_ALARM_CONTROL_AF) {
		ret = IRQ_HANDLED;
		rtc7301_alarm_irq(priv, false);
		rtc_update_irq(rtc, 1, RTC_IRQF | RTC_AF);
	}

	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;
}
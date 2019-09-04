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
struct rtc7301_priv {scalar_t__ irq; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rtc7301_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc7301_alarm_irq (struct rtc7301_priv*,unsigned int) ; 
 int /*<<< orphan*/  rtc7301_select_bank (struct rtc7301_priv*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rtc7301_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct rtc7301_priv *priv = dev_get_drvdata(dev);
	unsigned long flags;

	if (priv->irq <= 0)
		return -EINVAL;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 1);
	rtc7301_alarm_irq(priv, enabled);

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}
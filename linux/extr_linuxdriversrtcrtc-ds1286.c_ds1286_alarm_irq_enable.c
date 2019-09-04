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
struct ds1286_priv {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CMD ; 
 unsigned char RTC_TDM ; 
 struct ds1286_priv* dev_get_drvdata (struct device*) ; 
 unsigned char ds1286_rtc_read (struct ds1286_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1286_rtc_write (struct ds1286_priv*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ds1286_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct ds1286_priv *priv = dev_get_drvdata(dev);
	unsigned long flags;
	unsigned char val;

	/* Allow or mask alarm interrupts */
	spin_lock_irqsave(&priv->lock, flags);
	val = ds1286_rtc_read(priv, RTC_CMD);
	if (enabled)
		val &=  ~RTC_TDM;
	else
		val |=  RTC_TDM;
	ds1286_rtc_write(priv, val, RTC_CMD);
	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}
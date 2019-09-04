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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct mutex {int dummy; } ;
struct rtc_device {struct mutex ops_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mcp795_update_alarm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int) ; 
 struct rtc_device* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static irqreturn_t mcp795_irq(int irq, void *data)
{
	struct spi_device *spi = data;
	struct rtc_device *rtc = spi_get_drvdata(spi);
	struct mutex *lock = &rtc->ops_lock;
	int ret;

	mutex_lock(lock);

	/* Disable alarm.
	 * There is no need to clear ALM0IF (Alarm 0 Interrupt Flag) bit,
	 * because it is done every time when alarm is enabled.
	 */
	ret = mcp795_update_alarm(&spi->dev, false);
	if (ret)
		dev_err(&spi->dev,
			"Failed to disable alarm in IRQ (ret=%d)\n", ret);
	rtc_update_irq(rtc, 1, RTC_AF | RTC_IRQF);

	mutex_unlock(lock);

	return IRQ_HANDLED;
}
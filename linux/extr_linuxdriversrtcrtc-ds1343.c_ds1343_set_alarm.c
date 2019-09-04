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
struct TYPE_2__ {int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct ds1343_priv {scalar_t__ irq; int /*<<< orphan*/  mutex; int /*<<< orphan*/  irqen; int /*<<< orphan*/  alarm_mday; int /*<<< orphan*/  alarm_hour; int /*<<< orphan*/  alarm_min; int /*<<< orphan*/  alarm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTC_AF ; 
 struct ds1343_priv* dev_get_drvdata (struct device*) ; 
 int ds1343_update_alarm (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1343_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct ds1343_priv *priv = dev_get_drvdata(dev);
	int res = 0;

	if (priv->irq <= 0)
		return -EINVAL;

	mutex_lock(&priv->mutex);

	priv->alarm_sec = alarm->time.tm_sec;
	priv->alarm_min = alarm->time.tm_min;
	priv->alarm_hour = alarm->time.tm_hour;
	priv->alarm_mday = alarm->time.tm_mday;

	if (alarm->enabled)
		priv->irqen |= RTC_AF;

	res = ds1343_update_alarm(dev);

	mutex_unlock(&priv->mutex);

	return res;
}
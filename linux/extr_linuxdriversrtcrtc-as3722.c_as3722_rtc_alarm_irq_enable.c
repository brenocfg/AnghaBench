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
struct device {int dummy; } ;
struct as3722_rtc {int irq_enable; int /*<<< orphan*/  alarm_irq; } ;

/* Variables and functions */
 struct as3722_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as3722_rtc_alarm_irq_enable(struct device *dev,
		unsigned int enabled)
{
	struct as3722_rtc *as3722_rtc = dev_get_drvdata(dev);

	if (enabled && !as3722_rtc->irq_enable) {
		enable_irq(as3722_rtc->alarm_irq);
		as3722_rtc->irq_enable = true;
	} else if (!enabled && as3722_rtc->irq_enable)  {
		disable_irq(as3722_rtc->alarm_irq);
		as3722_rtc->irq_enable = false;
	}
	return 0;
}
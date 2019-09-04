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
struct st_rtc {int irq_enabled; int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct st_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct st_rtc *rtc = dev_get_drvdata(dev);

	if (enabled && !rtc->irq_enabled) {
		enable_irq(rtc->irq);
		rtc->irq_enabled = true;
	} else if (!enabled && rtc->irq_enabled) {
		disable_irq(rtc->irq);
		rtc->irq_enabled = false;
	}

	return 0;
}
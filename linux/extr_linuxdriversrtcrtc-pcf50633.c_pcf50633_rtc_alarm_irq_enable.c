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
struct pcf50633_rtc {unsigned int alarm_enabled; int /*<<< orphan*/  pcf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF50633_IRQ_ALARM ; 
 struct pcf50633_rtc* dev_get_drvdata (struct device*) ; 
 int pcf50633_irq_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcf50633_irq_unmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcf50633_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct pcf50633_rtc *rtc = dev_get_drvdata(dev);
	int err;

	if (enabled)
		err = pcf50633_irq_unmask(rtc->pcf, PCF50633_IRQ_ALARM);
	else
		err = pcf50633_irq_mask(rtc->pcf, PCF50633_IRQ_ALARM);

	if (err < 0)
		return err;

	rtc->alarm_enabled = enabled;

	return 0;
}
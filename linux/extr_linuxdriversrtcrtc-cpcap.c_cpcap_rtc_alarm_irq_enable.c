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
struct cpcap_rtc {unsigned int alarm_enabled; int /*<<< orphan*/  alarm_irq; } ;

/* Variables and functions */
 struct cpcap_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct cpcap_rtc *rtc = dev_get_drvdata(dev);

	if (rtc->alarm_enabled == enabled)
		return 0;

	if (enabled)
		enable_irq(rtc->alarm_irq);
	else
		disable_irq(rtc->alarm_irq);

	rtc->alarm_enabled = !!enabled;

	return 0;
}
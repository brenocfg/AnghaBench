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
struct spear_rtc_config {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct spear_rtc_config* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spear_rtc_clear_interrupt (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  spear_rtc_disable_interrupt (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  spear_rtc_enable_interrupt (struct spear_rtc_config*) ; 

__attribute__((used)) static int spear_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct spear_rtc_config *config = dev_get_drvdata(dev);
	int ret = 0;

	spear_rtc_clear_interrupt(config);

	switch (enabled) {
	case 0:
		/* alarm off */
		spear_rtc_disable_interrupt(config);
		break;
	case 1:
		/* alarm on */
		spear_rtc_enable_interrupt(config);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
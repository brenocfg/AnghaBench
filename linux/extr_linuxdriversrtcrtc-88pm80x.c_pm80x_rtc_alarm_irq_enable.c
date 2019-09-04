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
struct pm80x_rtc_info {int /*<<< orphan*/  map; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM800_ALARM1_EN ; 
 int /*<<< orphan*/  PM800_RTC_CONTROL ; 
 struct pm80x_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm80x_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct pm80x_rtc_info *info = dev_get_drvdata(dev);

	if (enabled)
		regmap_update_bits(info->map, PM800_RTC_CONTROL,
				   PM800_ALARM1_EN, PM800_ALARM1_EN);
	else
		regmap_update_bits(info->map, PM800_RTC_CONTROL,
				   PM800_ALARM1_EN, 0);
	return 0;
}
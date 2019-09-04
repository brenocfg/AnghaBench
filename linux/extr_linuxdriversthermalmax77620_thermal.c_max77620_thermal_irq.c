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
struct max77620_therm_info {int irq_tjalarm1; int irq_tjalarm2; int /*<<< orphan*/  tz_device; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t max77620_thermal_irq(int irq, void *data)
{
	struct max77620_therm_info *mtherm = data;

	if (irq == mtherm->irq_tjalarm1)
		dev_warn(mtherm->dev, "Junction Temp Alarm1(120C) occurred\n");
	else if (irq == mtherm->irq_tjalarm2)
		dev_crit(mtherm->dev, "Junction Temp Alarm2(140C) occurred\n");

	thermal_zone_device_update(mtherm->tz_device,
				   THERMAL_EVENT_UNSPECIFIED);

	return IRQ_HANDLED;
}
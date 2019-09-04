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
struct rt9455_info {scalar_t__ charger; int /*<<< orphan*/ * regmap_fields; TYPE_1__* client; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int irq; struct device dev; } ;

/* Variables and functions */
 size_t F_STAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  power_supply_changed (scalar_t__) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 
 int rt9455_irq_handler_check_irq1_register (struct rt9455_info*,int*,int*) ; 
 int rt9455_irq_handler_check_irq2_register (struct rt9455_info*,int,int*) ; 
 int rt9455_irq_handler_check_irq3_register (struct rt9455_info*,int*) ; 

__attribute__((used)) static irqreturn_t rt9455_irq_handler_thread(int irq, void *data)
{
	struct rt9455_info *info = data;
	struct device *dev;
	bool alert_userspace = false;
	bool is_battery_absent = false;
	unsigned int status;
	int ret;

	if (!info)
		return IRQ_NONE;

	dev = &info->client->dev;

	if (irq != info->client->irq) {
		dev_err(dev, "Interrupt is not for RT9455 charger\n");
		return IRQ_NONE;
	}

	ret = regmap_field_read(info->regmap_fields[F_STAT], &status);
	if (ret) {
		dev_err(dev, "Failed to read STAT bits\n");
		return IRQ_HANDLED;
	}
	dev_dbg(dev, "Charger status is %d\n", status);

	/*
	 * Each function that processes an IRQ register receives as output
	 * parameter alert_userspace pointer. alert_userspace is set to true
	 * in such a function only if an interrupt has occurred in the
	 * respective interrupt register. This way, it is avoided the following
	 * case: interrupt occurs only in IRQ1 register,
	 * rt9455_irq_handler_check_irq1_register() function sets to true
	 * alert_userspace, but rt9455_irq_handler_check_irq2_register()
	 * and rt9455_irq_handler_check_irq3_register() functions set to false
	 * alert_userspace and power_supply_changed() is never called.
	 */
	ret = rt9455_irq_handler_check_irq1_register(info, &is_battery_absent,
						     &alert_userspace);
	if (ret) {
		dev_err(dev, "Failed to handle IRQ1 register\n");
		return IRQ_HANDLED;
	}

	ret = rt9455_irq_handler_check_irq2_register(info, is_battery_absent,
						     &alert_userspace);
	if (ret) {
		dev_err(dev, "Failed to handle IRQ2 register\n");
		return IRQ_HANDLED;
	}

	ret = rt9455_irq_handler_check_irq3_register(info, &alert_userspace);
	if (ret) {
		dev_err(dev, "Failed to handle IRQ3 register\n");
		return IRQ_HANDLED;
	}

	if (alert_userspace) {
		/*
		 * Sometimes, an interrupt occurs while rt9455_probe() function
		 * is executing and power_supply_register() is not yet called.
		 * Do not call power_supply_changed() in this case.
		 */
		if (info->charger)
			power_supply_changed(info->charger);
	}

	return IRQ_HANDLED;
}
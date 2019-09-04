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
struct thermal_zone_device {int dummy; } ;
struct max8973_chip {scalar_t__ id; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 scalar_t__ MAX77621 ; 
 int PTR_ERR (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct max8973_chip*) ; 
 struct thermal_zone_device* devm_thermal_zone_of_sensor_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct max8973_chip*,int /*<<< orphan*/ *) ; 
 struct irq_data* irq_get_irq_data (int /*<<< orphan*/ ) ; 
 unsigned long irqd_get_trigger_type (struct irq_data*) ; 
 int /*<<< orphan*/  max77621_tz_ops ; 
 int /*<<< orphan*/  max8973_thermal_irq ; 

__attribute__((used)) static int max8973_thermal_init(struct max8973_chip *mchip)
{
	struct thermal_zone_device *tzd;
	struct irq_data *irq_data;
	unsigned long irq_flags = 0;
	int ret;

	if (mchip->id != MAX77621)
		return 0;

	tzd = devm_thermal_zone_of_sensor_register(mchip->dev, 0, mchip,
						   &max77621_tz_ops);
	if (IS_ERR(tzd)) {
		ret = PTR_ERR(tzd);
		dev_err(mchip->dev, "Failed to register thermal sensor: %d\n",
			ret);
		return ret;
	}

	if (mchip->irq <= 0)
		return 0;

	irq_data = irq_get_irq_data(mchip->irq);
	if (irq_data)
		irq_flags = irqd_get_trigger_type(irq_data);

	ret = devm_request_threaded_irq(mchip->dev, mchip->irq, NULL,
					max8973_thermal_irq,
					IRQF_ONESHOT | IRQF_SHARED | irq_flags,
					dev_name(mchip->dev), mchip);
	if (ret < 0) {
		dev_err(mchip->dev, "Failed to request irq %d, %d\n",
			mchip->irq, ret);
		return ret;
	}

	return 0;
}
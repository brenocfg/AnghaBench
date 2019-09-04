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
struct platform_device {struct device dev; } ;
struct da9150_charger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  free_irq (int,struct da9150_charger*) ; 
 struct da9150_charger* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq_byname (struct platform_device*,char const*) ; 

__attribute__((used)) static void da9150_charger_unregister_irq(struct platform_device *pdev,
					  const char *irq_name)
{
	struct device *dev = &pdev->dev;
	struct da9150_charger *charger = platform_get_drvdata(pdev);
	int irq;

	irq = platform_get_irq_byname(pdev, irq_name);
	if (irq < 0) {
		dev_err(dev, "Failed to get IRQ CHG_STATUS: %d\n", irq);
		return;
	}

	free_irq(irq, charger);
}
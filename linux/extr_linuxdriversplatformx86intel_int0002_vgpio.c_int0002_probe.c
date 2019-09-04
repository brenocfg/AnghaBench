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
struct x86_cpu_id {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int need_valid_mask; int /*<<< orphan*/  valid_mask; } ;
struct gpio_chip {int base; TYPE_1__ irq; scalar_t__ ngpio; int /*<<< orphan*/  direction_output; void* direction_input; int /*<<< orphan*/  set; void* get; int /*<<< orphan*/  owner; struct device* parent; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPE0A_PME_B0_VIRT_GPIO_PIN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int devm_gpiochip_add_data (struct device*,struct gpio_chip*,int /*<<< orphan*/ *) ; 
 struct gpio_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct gpio_chip*) ; 
 int gpiochip_irqchip_add (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (struct gpio_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  int0002_cpu_ids ; 
 int /*<<< orphan*/  int0002_gpio_direction_output ; 
 void* int0002_gpio_get ; 
 int /*<<< orphan*/  int0002_gpio_set ; 
 int /*<<< orphan*/  int0002_irq ; 
 int /*<<< orphan*/  int0002_irqchip ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct x86_cpu_id* x86_match_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int0002_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct x86_cpu_id *cpu_id;
	struct gpio_chip *chip;
	int irq, ret;

	/* Menlow has a different INT0002 device? <sigh> */
	cpu_id = x86_match_cpu(int0002_cpu_ids);
	if (!cpu_id)
		return -ENODEV;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "Error getting IRQ: %d\n", irq);
		return irq;
	}

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->label = DRV_NAME;
	chip->parent = dev;
	chip->owner = THIS_MODULE;
	chip->get = int0002_gpio_get;
	chip->set = int0002_gpio_set;
	chip->direction_input = int0002_gpio_get;
	chip->direction_output = int0002_gpio_direction_output;
	chip->base = -1;
	chip->ngpio = GPE0A_PME_B0_VIRT_GPIO_PIN + 1;
	chip->irq.need_valid_mask = true;

	ret = devm_gpiochip_add_data(&pdev->dev, chip, NULL);
	if (ret) {
		dev_err(dev, "Error adding gpio chip: %d\n", ret);
		return ret;
	}

	bitmap_clear(chip->irq.valid_mask, 0, GPE0A_PME_B0_VIRT_GPIO_PIN);

	/*
	 * We manually request the irq here instead of passing a flow-handler
	 * to gpiochip_set_chained_irqchip, because the irq is shared.
	 */
	ret = devm_request_irq(dev, irq, int0002_irq,
			       IRQF_SHARED, "INT0002", chip);
	if (ret) {
		dev_err(dev, "Error requesting IRQ %d: %d\n", irq, ret);
		return ret;
	}

	ret = gpiochip_irqchip_add(chip, &int0002_irqchip, 0, handle_edge_irq,
				   IRQ_TYPE_NONE);
	if (ret) {
		dev_err(dev, "Error adding irqchip: %d\n", ret);
		return ret;
	}

	gpiochip_set_chained_irqchip(chip, &int0002_irqchip, irq, NULL);

	return 0;
}
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
typedef  int u32 ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct gpio_chip {int base; int ngpio; int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  label; } ;
struct iproc_gpio {int num_banks; int /*<<< orphan*/  pinmux_is_supported; struct gpio_chip gc; int /*<<< orphan*/  lock; void* io_ctrl; void* base; struct device* dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IPROC_PINCONF_DRIVE_STRENGTH ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (void*) ; 
 int NGPIOS_PER_BANK ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct iproc_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (struct gpio_chip*,struct iproc_gpio*) ; 
 int gpiochip_irqchip_add (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (struct gpio_chip*) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (struct gpio_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  iproc_gpio_direction_input ; 
 int /*<<< orphan*/  iproc_gpio_direction_output ; 
 int /*<<< orphan*/  iproc_gpio_free ; 
 int /*<<< orphan*/  iproc_gpio_get ; 
 int /*<<< orphan*/  iproc_gpio_irq_chip ; 
 int /*<<< orphan*/  iproc_gpio_irq_handler ; 
 int iproc_gpio_register_pinconf (struct iproc_gpio*) ; 
 int /*<<< orphan*/  iproc_gpio_request ; 
 int /*<<< orphan*/  iproc_gpio_set ; 
 int iproc_pinconf_disable_map_create (struct iproc_gpio*,int) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iproc_gpio*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iproc_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct iproc_gpio *chip;
	struct gpio_chip *gc;
	u32 ngpios, pinconf_disable_mask = 0;
	int irq, ret;
	bool no_pinconf = false;

	/* NSP does not support drive strength config */
	if (of_device_is_compatible(dev->of_node, "brcm,iproc-nsp-gpio"))
		pinconf_disable_mask = BIT(IPROC_PINCONF_DRIVE_STRENGTH);
	/* Stingray does not support pinconf in this controller */
	else if (of_device_is_compatible(dev->of_node,
					 "brcm,iproc-stingray-gpio"))
		no_pinconf = true;

	chip = devm_kzalloc(dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->dev = dev;
	platform_set_drvdata(pdev, chip);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	chip->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(chip->base)) {
		dev_err(dev, "unable to map I/O memory\n");
		return PTR_ERR(chip->base);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res) {
		chip->io_ctrl = devm_ioremap_resource(dev, res);
		if (IS_ERR(chip->io_ctrl)) {
			dev_err(dev, "unable to map I/O memory\n");
			return PTR_ERR(chip->io_ctrl);
		}
	}

	if (of_property_read_u32(dev->of_node, "ngpios", &ngpios)) {
		dev_err(&pdev->dev, "missing ngpios DT property\n");
		return -ENODEV;
	}

	raw_spin_lock_init(&chip->lock);

	gc = &chip->gc;
	gc->base = -1;
	gc->ngpio = ngpios;
	chip->num_banks = (ngpios + NGPIOS_PER_BANK - 1) / NGPIOS_PER_BANK;
	gc->label = dev_name(dev);
	gc->parent = dev;
	gc->of_node = dev->of_node;
	gc->request = iproc_gpio_request;
	gc->free = iproc_gpio_free;
	gc->direction_input = iproc_gpio_direction_input;
	gc->direction_output = iproc_gpio_direction_output;
	gc->set = iproc_gpio_set;
	gc->get = iproc_gpio_get;

	chip->pinmux_is_supported = of_property_read_bool(dev->of_node,
							"gpio-ranges");

	ret = gpiochip_add_data(gc, chip);
	if (ret < 0) {
		dev_err(dev, "unable to add GPIO chip\n");
		return ret;
	}

	if (!no_pinconf) {
		ret = iproc_gpio_register_pinconf(chip);
		if (ret) {
			dev_err(dev, "unable to register pinconf\n");
			goto err_rm_gpiochip;
		}

		if (pinconf_disable_mask) {
			ret = iproc_pinconf_disable_map_create(chip,
							 pinconf_disable_mask);
			if (ret) {
				dev_err(dev,
					"unable to create pinconf disable map\n");
				goto err_rm_gpiochip;
			}
		}
	}

	/* optional GPIO interrupt support */
	irq = platform_get_irq(pdev, 0);
	if (irq) {
		ret = gpiochip_irqchip_add(gc, &iproc_gpio_irq_chip, 0,
					   handle_simple_irq, IRQ_TYPE_NONE);
		if (ret) {
			dev_err(dev, "no GPIO irqchip\n");
			goto err_rm_gpiochip;
		}

		gpiochip_set_chained_irqchip(gc, &iproc_gpio_irq_chip, irq,
					     iproc_gpio_irq_handler);
	}

	return 0;

err_rm_gpiochip:
	gpiochip_remove(gc);

	return ret;
}
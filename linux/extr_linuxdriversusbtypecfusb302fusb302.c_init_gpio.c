#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fusb302_chip {int gpio_int_n; int gpio_int_n_irq; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int devm_gpio_request (TYPE_1__*,int,char*) ; 
 int gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int gpio_to_irq (int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_gpio(struct fusb302_chip *chip)
{
	struct device_node *node;
	int ret = 0;

	node = chip->dev->of_node;
	chip->gpio_int_n = of_get_named_gpio(node, "fcs,int_n", 0);
	if (!gpio_is_valid(chip->gpio_int_n)) {
		ret = chip->gpio_int_n;
		dev_err(chip->dev, "cannot get named GPIO Int_N, ret=%d", ret);
		return ret;
	}
	ret = devm_gpio_request(chip->dev, chip->gpio_int_n, "fcs,int_n");
	if (ret < 0) {
		dev_err(chip->dev, "cannot request GPIO Int_N, ret=%d", ret);
		return ret;
	}
	ret = gpio_direction_input(chip->gpio_int_n);
	if (ret < 0) {
		dev_err(chip->dev,
			"cannot set GPIO Int_N to input, ret=%d", ret);
		return ret;
	}
	ret = gpio_to_irq(chip->gpio_int_n);
	if (ret < 0) {
		dev_err(chip->dev,
			"cannot request IRQ for GPIO Int_N, ret=%d", ret);
		return ret;
	}
	chip->gpio_int_n_irq = ret;
	return 0;
}
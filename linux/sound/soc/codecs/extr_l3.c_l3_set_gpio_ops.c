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
struct l3_pins {int /*<<< orphan*/  setmode; int /*<<< orphan*/  gpio_mode; int /*<<< orphan*/  setclk; int /*<<< orphan*/  gpio_clk; int /*<<< orphan*/  setdat; int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  use_gpios; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  l3_set_clk ; 
 int /*<<< orphan*/  l3_set_data ; 
 int /*<<< orphan*/  l3_set_mode ; 

int l3_set_gpio_ops(struct device *dev, struct l3_pins *adap)
{
	int ret;

	if (!adap->use_gpios)
		return -EINVAL;

	ret = devm_gpio_request_one(dev, adap->gpio_data,
				GPIOF_OUT_INIT_LOW, "l3_data");
	if (ret < 0)
		return ret;
	adap->setdat = l3_set_data;

	ret = devm_gpio_request_one(dev, adap->gpio_clk,
				GPIOF_OUT_INIT_LOW, "l3_clk");
	if (ret < 0)
		return ret;
	adap->setclk = l3_set_clk;

	ret = devm_gpio_request_one(dev, adap->gpio_mode,
				GPIOF_OUT_INIT_LOW, "l3_mode");
	if (ret < 0)
		return ret;
	adap->setmode = l3_set_mode;

	return 0;
}
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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ds2404_platform_data {int /*<<< orphan*/  gpio_dq; int /*<<< orphan*/  gpio_clk; int /*<<< orphan*/  gpio_rst; } ;
struct ds2404 {TYPE_1__* gpio; } ;
struct TYPE_3__ {int /*<<< orphan*/  gpio; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 size_t DS2404_CLK ; 
 size_t DS2404_DQ ; 
 size_t DS2404_RST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ds2404_gpio ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds2404_gpio_map(struct ds2404 *chip, struct platform_device *pdev,
			  struct ds2404_platform_data *pdata)
{
	int i, err;

	ds2404_gpio[DS2404_RST].gpio = pdata->gpio_rst;
	ds2404_gpio[DS2404_CLK].gpio = pdata->gpio_clk;
	ds2404_gpio[DS2404_DQ].gpio = pdata->gpio_dq;

	for (i = 0; i < ARRAY_SIZE(ds2404_gpio); i++) {
		err = gpio_request(ds2404_gpio[i].gpio, ds2404_gpio[i].name);
		if (err) {
			dev_err(&pdev->dev, "error mapping gpio %s: %d\n",
				ds2404_gpio[i].name, err);
			goto err_request;
		}
		if (i != DS2404_DQ)
			gpio_direction_output(ds2404_gpio[i].gpio, 1);
	}

	chip->gpio = ds2404_gpio;
	return 0;

err_request:
	while (--i >= 0)
		gpio_free(ds2404_gpio[i].gpio);
	return err;
}
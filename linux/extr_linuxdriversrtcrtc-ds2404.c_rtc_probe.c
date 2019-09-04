#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ds2404_platform_data {int dummy; } ;
struct ds2404 {TYPE_2__* ops; int /*<<< orphan*/  rtc; TYPE_1__* gpio; } ;
struct TYPE_4__ {int (* map_io ) (struct ds2404*,struct platform_device*,struct ds2404_platform_data*) ;int /*<<< orphan*/  (* unmap_io ) (struct ds2404*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 size_t DS2404_CLK ; 
 size_t DS2404_DQ ; 
 size_t DS2404_RST ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct ds2404_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ds2404* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds2404_enable_osc (int /*<<< orphan*/ *) ; 
 TYPE_2__ ds2404_gpio_ops ; 
 int /*<<< orphan*/  ds2404_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ds2404*) ; 
 int stub1 (struct ds2404*,struct platform_device*,struct ds2404_platform_data*) ; 
 int /*<<< orphan*/  stub2 (struct ds2404*) ; 

__attribute__((used)) static int rtc_probe(struct platform_device *pdev)
{
	struct ds2404_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct ds2404 *chip;
	int retval = -EBUSY;

	chip = devm_kzalloc(&pdev->dev, sizeof(struct ds2404), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->ops = &ds2404_gpio_ops;

	retval = chip->ops->map_io(chip, pdev, pdata);
	if (retval)
		goto err_chip;

	dev_info(&pdev->dev, "using GPIOs RST:%d, CLK:%d, DQ:%d\n",
		 chip->gpio[DS2404_RST].gpio, chip->gpio[DS2404_CLK].gpio,
		 chip->gpio[DS2404_DQ].gpio);

	platform_set_drvdata(pdev, chip);

	chip->rtc = devm_rtc_device_register(&pdev->dev, "ds2404",
					&ds2404_rtc_ops, THIS_MODULE);
	if (IS_ERR(chip->rtc)) {
		retval = PTR_ERR(chip->rtc);
		goto err_io;
	}

	ds2404_enable_osc(&pdev->dev);
	return 0;

err_io:
	chip->ops->unmap_io(chip);
err_chip:
	return retval;
}
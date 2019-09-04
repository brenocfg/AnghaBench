#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pm860x_power_pdata {int max_capacity; int resistor; } ;
struct pm860x_chip {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  companion; int /*<<< orphan*/  client; } ;
struct pm860x_battery_info {scalar_t__ irq_cc; scalar_t__ irq_batt; int max_capacity; int resistor; TYPE_2__* battery; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; TYPE_3__* dev; int /*<<< orphan*/  i2c; struct pm860x_chip* chip; } ;
struct TYPE_10__ {struct pm860x_power_pdata* platform_data; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_PM8607 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct pm860x_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct pm860x_battery_info* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_power_supply_register (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pm860x_battery_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm860x_battery_info*) ; 
 int /*<<< orphan*/  pm860x_batt_handler ; 
 int /*<<< orphan*/  pm860x_battery_desc ; 
 int /*<<< orphan*/  pm860x_coulomb_handler ; 
 int /*<<< orphan*/  pm860x_init_battery (struct pm860x_battery_info*) ; 

__attribute__((used)) static int pm860x_battery_probe(struct platform_device *pdev)
{
	struct pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct pm860x_battery_info *info;
	struct pm860x_power_pdata *pdata;
	int ret;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->irq_cc = platform_get_irq(pdev, 0);
	if (info->irq_cc <= 0) {
		dev_err(&pdev->dev, "No IRQ resource!\n");
		return -EINVAL;
	}

	info->irq_batt = platform_get_irq(pdev, 1);
	if (info->irq_batt <= 0) {
		dev_err(&pdev->dev, "No IRQ resource!\n");
		return -EINVAL;
	}

	info->chip = chip;
	info->i2c =
	    (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->dev = &pdev->dev;
	info->status = POWER_SUPPLY_STATUS_UNKNOWN;
	pdata = pdev->dev.platform_data;

	mutex_init(&info->lock);
	platform_set_drvdata(pdev, info);

	pm860x_init_battery(info);

	if (pdata && pdata->max_capacity)
		info->max_capacity = pdata->max_capacity;
	else
		info->max_capacity = 1500;	/* set default capacity */
	if (pdata && pdata->resistor)
		info->resistor = pdata->resistor;
	else
		info->resistor = 300;	/* set default internal resistor */

	info->battery = devm_power_supply_register(&pdev->dev,
						   &pm860x_battery_desc,
						   NULL);
	if (IS_ERR(info->battery))
		return PTR_ERR(info->battery);
	info->battery->dev.parent = &pdev->dev;

	ret = devm_request_threaded_irq(chip->dev, info->irq_cc, NULL,
					pm860x_coulomb_handler, IRQF_ONESHOT,
					"coulomb", info);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq_cc, ret);
		return ret;
	}

	ret = devm_request_threaded_irq(chip->dev, info->irq_batt, NULL,
					pm860x_batt_handler,
					IRQF_ONESHOT, "battery", info);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq_batt, ret);
		return ret;
	}


	return 0;
}
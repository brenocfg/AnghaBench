#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct virtual_consumer_data {int /*<<< orphan*/  regulator; int /*<<< orphan*/  mode; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 char* dev_get_platdata (TYPE_1__*) ; 
 struct virtual_consumer_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct virtual_consumer_data*) ; 
 int /*<<< orphan*/  regulator_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_virtual_attr_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int regulator_virtual_probe(struct platform_device *pdev)
{
	char *reg_id = dev_get_platdata(&pdev->dev);
	struct virtual_consumer_data *drvdata;
	int ret;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(struct virtual_consumer_data),
			       GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;

	mutex_init(&drvdata->lock);

	drvdata->regulator = devm_regulator_get(&pdev->dev, reg_id);
	if (IS_ERR(drvdata->regulator)) {
		ret = PTR_ERR(drvdata->regulator);
		dev_err(&pdev->dev, "Failed to obtain supply '%s': %d\n",
			reg_id, ret);
		return ret;
	}

	ret = sysfs_create_group(&pdev->dev.kobj,
				 &regulator_virtual_attr_group);
	if (ret != 0) {
		dev_err(&pdev->dev,
			"Failed to create attribute group: %d\n", ret);
		return ret;
	}

	drvdata->mode = regulator_get_mode(drvdata->regulator);

	platform_set_drvdata(pdev, drvdata);

	return 0;
}
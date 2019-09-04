#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qoriq_tmu_data {int sensor_id; TYPE_1__* regs; int /*<<< orphan*/  tz; int /*<<< orphan*/  little_endian; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tmr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TMR_ALPF ; 
 int TMR_ME ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct qoriq_tmu_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_thermal_zone_of_sensor_register (TYPE_3__*,int,struct qoriq_tmu_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (TYPE_1__*) ; 
 TYPE_1__* of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qoriq_tmu_data*) ; 
 int qoriq_tmu_calibration (struct platform_device*) ; 
 int qoriq_tmu_get_sensor_id () ; 
 int /*<<< orphan*/  qoriq_tmu_init_device (struct qoriq_tmu_data*) ; 
 int /*<<< orphan*/  tmu_tz_ops ; 
 int /*<<< orphan*/  tmu_write (struct qoriq_tmu_data*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qoriq_tmu_probe(struct platform_device *pdev)
{
	int ret;
	struct qoriq_tmu_data *data;
	struct device_node *np = pdev->dev.of_node;
	u32 site;

	if (!np) {
		dev_err(&pdev->dev, "Device OF-Node is NULL");
		return -ENODEV;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(struct qoriq_tmu_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);

	data->little_endian = of_property_read_bool(np, "little-endian");

	data->sensor_id = qoriq_tmu_get_sensor_id();
	if (data->sensor_id < 0) {
		dev_err(&pdev->dev, "Failed to get sensor id\n");
		ret = -ENODEV;
		goto err_iomap;
	}

	data->regs = of_iomap(np, 0);
	if (!data->regs) {
		dev_err(&pdev->dev, "Failed to get memory region\n");
		ret = -ENODEV;
		goto err_iomap;
	}

	qoriq_tmu_init_device(data);	/* TMU initialization */

	ret = qoriq_tmu_calibration(pdev);	/* TMU calibration */
	if (ret < 0)
		goto err_tmu;

	data->tz = devm_thermal_zone_of_sensor_register(&pdev->dev,
							data->sensor_id,
							data, &tmu_tz_ops);
	if (IS_ERR(data->tz)) {
		ret = PTR_ERR(data->tz);
		dev_err(&pdev->dev,
			"Failed to register thermal zone device %d\n", ret);
		goto err_tmu;
	}

	/* Enable monitoring */
	site = 0x1 << (15 - data->sensor_id);
	tmu_write(data, site | TMR_ME | TMR_ALPF, &data->regs->tmr);

	return 0;

err_tmu:
	iounmap(data->regs);

err_iomap:
	platform_set_drvdata(pdev, NULL);

	return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct db8500_thsens_platform_data {TYPE_1__* trip_points; int /*<<< orphan*/  num_trips; } ;
struct db8500_thermal_zone {int /*<<< orphan*/  th_lock; int /*<<< orphan*/  mode; int /*<<< orphan*/  therm_dev; int /*<<< orphan*/  therm_work; struct db8500_thsens_platform_data* trip_tab; } ;
struct TYPE_7__ {unsigned long temp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned long PRCMU_DEFAULT_LOW_TEMP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THERMAL_DEVICE_DISABLED ; 
 int /*<<< orphan*/  THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  THERMAL_TREND_STABLE ; 
 struct db8500_thsens_platform_data* db8500_thermal_parse_dt (struct platform_device*) ; 
 int /*<<< orphan*/  db8500_thermal_update_config (struct db8500_thermal_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  db8500_thermal_work ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct db8500_thsens_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 struct db8500_thermal_zone* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct db8500_thermal_zone*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct db8500_thermal_zone*) ; 
 int /*<<< orphan*/  prcmu_high_irq_handler ; 
 int /*<<< orphan*/  prcmu_low_irq_handler ; 
 int /*<<< orphan*/  thdev_ops ; 
 int /*<<< orphan*/  thermal_zone_device_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct db8500_thermal_zone*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db8500_thermal_probe(struct platform_device *pdev)
{
	struct db8500_thermal_zone *pzone = NULL;
	struct db8500_thsens_platform_data *ptrips = NULL;
	struct device_node *np = pdev->dev.of_node;
	int low_irq, high_irq, ret = 0;
	unsigned long dft_low, dft_high;

	if (np)
		ptrips = db8500_thermal_parse_dt(pdev);
	else
		ptrips = dev_get_platdata(&pdev->dev);

	if (!ptrips)
		return -EINVAL;

	pzone = devm_kzalloc(&pdev->dev, sizeof(*pzone), GFP_KERNEL);
	if (!pzone)
		return -ENOMEM;

	mutex_init(&pzone->th_lock);
	mutex_lock(&pzone->th_lock);

	pzone->mode = THERMAL_DEVICE_DISABLED;
	pzone->trip_tab = ptrips;

	INIT_WORK(&pzone->therm_work, db8500_thermal_work);

	low_irq = platform_get_irq_byname(pdev, "IRQ_HOTMON_LOW");
	if (low_irq < 0) {
		dev_err(&pdev->dev, "Get IRQ_HOTMON_LOW failed.\n");
		ret = low_irq;
		goto out_unlock;
	}

	ret = devm_request_threaded_irq(&pdev->dev, low_irq, NULL,
		prcmu_low_irq_handler, IRQF_NO_SUSPEND | IRQF_ONESHOT,
		"dbx500_temp_low", pzone);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to allocate temp low irq.\n");
		goto out_unlock;
	}

	high_irq = platform_get_irq_byname(pdev, "IRQ_HOTMON_HIGH");
	if (high_irq < 0) {
		dev_err(&pdev->dev, "Get IRQ_HOTMON_HIGH failed.\n");
		ret = high_irq;
		goto out_unlock;
	}

	ret = devm_request_threaded_irq(&pdev->dev, high_irq, NULL,
		prcmu_high_irq_handler, IRQF_NO_SUSPEND | IRQF_ONESHOT,
		"dbx500_temp_high", pzone);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to allocate temp high irq.\n");
		goto out_unlock;
	}

	pzone->therm_dev = thermal_zone_device_register("db8500_thermal_zone",
		ptrips->num_trips, 0, pzone, &thdev_ops, NULL, 0, 0);

	if (IS_ERR(pzone->therm_dev)) {
		dev_err(&pdev->dev, "Register thermal zone device failed.\n");
		ret = PTR_ERR(pzone->therm_dev);
		goto out_unlock;
	}
	dev_info(&pdev->dev, "Thermal zone device registered.\n");

	dft_low = PRCMU_DEFAULT_LOW_TEMP;
	dft_high = ptrips->trip_points[0].temp;

	db8500_thermal_update_config(pzone, 0, THERMAL_TREND_STABLE,
		dft_low, dft_high);

	platform_set_drvdata(pdev, pzone);
	pzone->mode = THERMAL_DEVICE_ENABLED;

out_unlock:
	mutex_unlock(&pzone->th_lock);

	return ret;
}
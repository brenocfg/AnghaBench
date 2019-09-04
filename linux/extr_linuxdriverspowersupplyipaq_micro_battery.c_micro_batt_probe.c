#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct micro_battery {int /*<<< orphan*/  wq; int /*<<< orphan*/  update; int /*<<< orphan*/  micro; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct micro_battery* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  micro_ac_power ; 
 int /*<<< orphan*/  micro_ac_power_desc ; 
 int /*<<< orphan*/  micro_batt_power ; 
 int /*<<< orphan*/  micro_batt_power_desc ; 
 int /*<<< orphan*/  micro_battery_work ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct micro_battery*) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int micro_batt_probe(struct platform_device *pdev)
{
	struct micro_battery *mb;
	int ret;

	mb = devm_kzalloc(&pdev->dev, sizeof(*mb), GFP_KERNEL);
	if (!mb)
		return -ENOMEM;

	mb->micro = dev_get_drvdata(pdev->dev.parent);
	mb->wq = alloc_workqueue("ipaq-battery-wq", WQ_MEM_RECLAIM, 0);
	if (!mb->wq)
		return -ENOMEM;

	INIT_DELAYED_WORK(&mb->update, micro_battery_work);
	platform_set_drvdata(pdev, mb);
	queue_delayed_work(mb->wq, &mb->update, 1);

	micro_batt_power = power_supply_register(&pdev->dev,
						 &micro_batt_power_desc, NULL);
	if (IS_ERR(micro_batt_power)) {
		ret = PTR_ERR(micro_batt_power);
		goto batt_err;
	}

	micro_ac_power = power_supply_register(&pdev->dev,
					       &micro_ac_power_desc, NULL);
	if (IS_ERR(micro_ac_power)) {
		ret = PTR_ERR(micro_ac_power);
		goto ac_err;
	}

	dev_info(&pdev->dev, "iPAQ micro battery driver\n");
	return 0;

ac_err:
	power_supply_unregister(micro_batt_power);
batt_err:
	cancel_delayed_work_sync(&mb->update);
	destroy_workqueue(mb->wq);
	return ret;
}
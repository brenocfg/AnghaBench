#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtual_consumer_data {int /*<<< orphan*/  regulator; scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct virtual_consumer_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_virtual_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int regulator_virtual_remove(struct platform_device *pdev)
{
	struct virtual_consumer_data *drvdata = platform_get_drvdata(pdev);

	sysfs_remove_group(&pdev->dev.kobj, &regulator_virtual_attr_group);

	if (drvdata->enabled)
		regulator_disable(drvdata->regulator);

	return 0;
}
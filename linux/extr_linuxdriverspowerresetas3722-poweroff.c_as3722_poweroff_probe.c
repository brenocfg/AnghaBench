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
struct TYPE_3__ {TYPE_2__* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct as3722_poweroff {TYPE_1__* dev; int /*<<< orphan*/  as3722; } ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ as3722_pm_power_off ; 
 struct as3722_poweroff* as3722_pm_poweroff ; 
 int /*<<< orphan*/  dev_get_drvdata (TYPE_2__*) ; 
 struct as3722_poweroff* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ pm_power_off ; 

__attribute__((used)) static int as3722_poweroff_probe(struct platform_device *pdev)
{
	struct as3722_poweroff *as3722_poweroff;
	struct device_node *np = pdev->dev.parent->of_node;

	if (!np)
		return -EINVAL;

	if (!of_property_read_bool(np, "ams,system-power-controller"))
		return 0;

	as3722_poweroff = devm_kzalloc(&pdev->dev, sizeof(*as3722_poweroff),
				GFP_KERNEL);
	if (!as3722_poweroff)
		return -ENOMEM;

	as3722_poweroff->as3722 = dev_get_drvdata(pdev->dev.parent);
	as3722_poweroff->dev = &pdev->dev;
	as3722_pm_poweroff = as3722_poweroff;
	if (!pm_power_off)
		pm_power_off = as3722_pm_power_off;

	return 0;
}
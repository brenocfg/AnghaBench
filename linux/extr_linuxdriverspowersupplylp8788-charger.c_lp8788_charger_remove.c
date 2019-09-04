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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct lp8788_charger {int /*<<< orphan*/  charger_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lp8788_attr_group ; 
 int /*<<< orphan*/  lp8788_irq_unregister (struct platform_device*,struct lp8788_charger*) ; 
 int /*<<< orphan*/  lp8788_psy_unregister (struct lp8788_charger*) ; 
 int /*<<< orphan*/  lp8788_release_adc_channel (struct lp8788_charger*) ; 
 struct lp8788_charger* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp8788_charger_remove(struct platform_device *pdev)
{
	struct lp8788_charger *pchg = platform_get_drvdata(pdev);

	flush_work(&pchg->charger_work);
	lp8788_irq_unregister(pdev, pchg);
	sysfs_remove_group(&pdev->dev.kobj, &lp8788_attr_group);
	lp8788_psy_unregister(pchg);
	lp8788_release_adc_channel(pchg);

	return 0;
}
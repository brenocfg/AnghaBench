#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gsw_mt753x {scalar_t__ irq; scalar_t__ reset_pin; int /*<<< orphan*/  irq_worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_gpio_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mt753x_remove_gsw (struct gsw_mt753x*) ; 
 int /*<<< orphan*/  mt753x_swconfig_destroy (struct gsw_mt753x*) ; 
 struct gsw_mt753x* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt753x_remove(struct platform_device *pdev)
{
	struct gsw_mt753x *gsw = platform_get_drvdata(pdev);

	if (gsw->irq >= 0)
		cancel_work_sync(&gsw->irq_worker);

	if (gsw->reset_pin >= 0)
		devm_gpio_free(&pdev->dev, gsw->reset_pin);

#ifdef CONFIG_SWCONFIG
	mt753x_swconfig_destroy(gsw);
#endif

	mt753x_remove_gsw(gsw);

	platform_set_drvdata(pdev, NULL);

	return 0;
}
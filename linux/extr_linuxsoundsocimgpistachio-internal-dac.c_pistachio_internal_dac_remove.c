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
struct pistachio_internal_dac {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 struct pistachio_internal_dac* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pistachio_internal_dac_pwr_off (struct pistachio_internal_dac*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pistachio_internal_dac_remove(struct platform_device *pdev)
{
	struct pistachio_internal_dac *dac = dev_get_drvdata(&pdev->dev);

	pm_runtime_disable(&pdev->dev);
	pistachio_internal_dac_pwr_off(dac);
	regulator_disable(dac->supply);

	return 0;
}
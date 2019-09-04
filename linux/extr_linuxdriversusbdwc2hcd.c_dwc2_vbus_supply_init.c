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
struct dwc2_hsotg {int /*<<< orphan*/ * vbus_supply; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (int /*<<< orphan*/ ,char*) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dwc2_vbus_supply_init(struct dwc2_hsotg *hsotg)
{
	int ret;

	hsotg->vbus_supply = devm_regulator_get_optional(hsotg->dev, "vbus");
	if (IS_ERR(hsotg->vbus_supply)) {
		ret = PTR_ERR(hsotg->vbus_supply);
		hsotg->vbus_supply = NULL;
		return ret == -ENODEV ? 0 : ret;
	}

	return regulator_enable(hsotg->vbus_supply);
}
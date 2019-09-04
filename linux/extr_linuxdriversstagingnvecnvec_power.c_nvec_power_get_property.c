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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct nvec_power {int /*<<< orphan*/  on; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 struct nvec_power* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvec_power_get_property(struct power_supply *psy,
				   enum power_supply_property psp,
				   union power_supply_propval *val)
{
	struct nvec_power *power = dev_get_drvdata(psy->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = power->on;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
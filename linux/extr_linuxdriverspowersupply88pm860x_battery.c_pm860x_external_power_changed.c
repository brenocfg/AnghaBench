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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct pm860x_battery_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_resistor (struct pm860x_battery_info*) ; 
 struct pm860x_battery_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm860x_external_power_changed(struct power_supply *psy)
{
	struct pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);

	calc_resistor(info);
}
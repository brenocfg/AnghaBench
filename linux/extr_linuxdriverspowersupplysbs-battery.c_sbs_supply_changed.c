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
struct sbs_info {int is_present; int /*<<< orphan*/  gpio_detect; struct power_supply* power_supply; } ;
struct power_supply {int dummy; } ;

/* Variables and functions */
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 

__attribute__((used)) static void sbs_supply_changed(struct sbs_info *chip)
{
	struct power_supply *battery = chip->power_supply;
	int ret;

	ret = gpiod_get_value_cansleep(chip->gpio_detect);
	if (ret < 0)
		return;
	chip->is_present = ret;
	power_supply_changed(battery);
}
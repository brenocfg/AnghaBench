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
struct da9062_watchdog {struct da9062* hw; } ;
struct da9062 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9062AA_CONTROL_D ; 
 int /*<<< orphan*/  DA9062AA_TWDSCALE_MASK ; 
 unsigned int DA9062_TWDSCALE_DISABLE ; 
 int da9062_reset_watchdog_timer (struct da9062_watchdog*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int da9062_wdt_update_timeout_register(struct da9062_watchdog *wdt,
					      unsigned int regval)
{
	struct da9062 *chip = wdt->hw;
	int ret;

	ret = da9062_reset_watchdog_timer(wdt);
	if (ret)
		return ret;

	regmap_update_bits(chip->regmap,
				  DA9062AA_CONTROL_D,
				  DA9062AA_TWDSCALE_MASK,
				  DA9062_TWDSCALE_DISABLE);

	usleep_range(150, 300);

	return regmap_update_bits(chip->regmap,
				  DA9062AA_CONTROL_D,
				  DA9062AA_TWDSCALE_MASK,
				  regval);
}
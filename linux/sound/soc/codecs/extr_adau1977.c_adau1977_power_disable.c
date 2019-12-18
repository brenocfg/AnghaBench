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
struct adau1977 {int enabled; scalar_t__ dvdd_reg; scalar_t__ avdd_reg; int /*<<< orphan*/  regmap; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1977_POWER_PWUP ; 
 int /*<<< orphan*/  ADAU1977_REG_POWER ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static int adau1977_power_disable(struct adau1977 *adau1977)
{
	int ret = 0;

	if (!adau1977->enabled)
		return 0;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_POWER,
		ADAU1977_POWER_PWUP, 0);
	if (ret)
		return ret;

	regcache_mark_dirty(adau1977->regmap);

	gpiod_set_value_cansleep(adau1977->reset_gpio, 0);

	regcache_cache_only(adau1977->regmap, true);

	regulator_disable(adau1977->avdd_reg);
	if (adau1977->dvdd_reg)
		regulator_disable(adau1977->dvdd_reg);

	adau1977->enabled = false;

	return 0;
}
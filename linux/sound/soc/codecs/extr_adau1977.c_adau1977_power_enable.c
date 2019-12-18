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
struct adau1977 {int enabled; scalar_t__ avdd_reg; scalar_t__ dvdd_reg; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* switch_mode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1977_POWER_PWUP ; 
 int /*<<< orphan*/  ADAU1977_REG_PLL ; 
 int /*<<< orphan*/  ADAU1977_REG_POWER ; 
 int adau1977_reset (struct adau1977*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1977_power_enable(struct adau1977 *adau1977)
{
	unsigned int val;
	int ret = 0;

	if (adau1977->enabled)
		return 0;

	ret = regulator_enable(adau1977->avdd_reg);
	if (ret)
		return ret;

	if (adau1977->dvdd_reg) {
		ret = regulator_enable(adau1977->dvdd_reg);
		if (ret)
			goto err_disable_avdd;
	}

	gpiod_set_value_cansleep(adau1977->reset_gpio, 1);

	regcache_cache_only(adau1977->regmap, false);

	if (adau1977->switch_mode)
		adau1977->switch_mode(adau1977->dev);

	ret = adau1977_reset(adau1977);
	if (ret)
		goto err_disable_dvdd;

	ret = regmap_update_bits(adau1977->regmap, ADAU1977_REG_POWER,
		ADAU1977_POWER_PWUP, ADAU1977_POWER_PWUP);
	if (ret)
		goto err_disable_dvdd;

	ret = regcache_sync(adau1977->regmap);
	if (ret)
		goto err_disable_dvdd;

	/*
	 * The PLL register is not affected by the software reset. It is
	 * possible that the value of the register was changed to the
	 * default value while we were in cache only mode. In this case
	 * regcache_sync will skip over it and we have to manually sync
	 * it.
	 */
	ret = regmap_read(adau1977->regmap, ADAU1977_REG_PLL, &val);
	if (ret)
		goto err_disable_dvdd;

	if (val == 0x41) {
		regcache_cache_bypass(adau1977->regmap, true);
		ret = regmap_write(adau1977->regmap, ADAU1977_REG_PLL,
			0x41);
		if (ret)
			goto err_disable_dvdd;
		regcache_cache_bypass(adau1977->regmap, false);
	}

	adau1977->enabled = true;

	return ret;

err_disable_dvdd:
	if (adau1977->dvdd_reg)
		regulator_disable(adau1977->dvdd_reg);
err_disable_avdd:
		regulator_disable(adau1977->avdd_reg);
	return ret;
}
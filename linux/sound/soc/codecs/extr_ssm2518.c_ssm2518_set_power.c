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
struct ssm2518 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  enable_gpio; } ;

/* Variables and functions */
 int SSM2518_POWER1_RESET ; 
 int SSM2518_POWER1_SPWDN ; 
 int /*<<< orphan*/  SSM2518_REG_POWER1 ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ssm2518_set_power(struct ssm2518 *ssm2518, bool enable)
{
	int ret = 0;

	if (!enable) {
		ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_SPWDN, SSM2518_POWER1_SPWDN);
		regcache_mark_dirty(ssm2518->regmap);
	}

	if (gpio_is_valid(ssm2518->enable_gpio))
		gpio_set_value(ssm2518->enable_gpio, enable);

	regcache_cache_only(ssm2518->regmap, !enable);

	if (enable) {
		ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
			SSM2518_POWER1_SPWDN | SSM2518_POWER1_RESET, 0x00);
		regcache_sync(ssm2518->regmap);
	}

	return ret;
}
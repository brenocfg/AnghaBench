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
struct ssm4567 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int SSM4567_POWER_SPWDN ; 
 int /*<<< orphan*/  SSM4567_REG_POWER_CTRL ; 
 int /*<<< orphan*/  SSM4567_REG_SOFT_RESET ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ssm4567_set_power(struct ssm4567 *ssm4567, bool enable)
{
	int ret = 0;

	if (!enable) {
		ret = regmap_update_bits(ssm4567->regmap,
			SSM4567_REG_POWER_CTRL,
			SSM4567_POWER_SPWDN, SSM4567_POWER_SPWDN);
		regcache_mark_dirty(ssm4567->regmap);
	}

	regcache_cache_only(ssm4567->regmap, !enable);

	if (enable) {
		ret = regmap_write(ssm4567->regmap, SSM4567_REG_SOFT_RESET,
			0x00);
		if (ret)
			return ret;

		ret = regmap_update_bits(ssm4567->regmap,
			SSM4567_REG_POWER_CTRL,
			SSM4567_POWER_SPWDN, 0x00);
		regcache_sync(ssm4567->regmap);
	}

	return ret;
}
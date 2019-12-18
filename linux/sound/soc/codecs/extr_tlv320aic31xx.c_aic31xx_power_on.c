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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct aic31xx_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int aic31xx_reset (struct aic31xx_priv*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aic31xx_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int aic31xx_power_on(struct snd_soc_component *component)
{
	struct aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(aic31xx->supplies),
				    aic31xx->supplies);
	if (ret)
		return ret;

	regcache_cache_only(aic31xx->regmap, false);

	/* Reset device registers for a consistent power-on like state */
	ret = aic31xx_reset(aic31xx);
	if (ret < 0)
		dev_err(aic31xx->dev, "Could not reset device: %d\n", ret);

	ret = regcache_sync(aic31xx->regmap);
	if (ret) {
		dev_err(component->dev,
			"Failed to restore cache: %d\n", ret);
		regcache_cache_only(aic31xx->regmap, true);
		regulator_bulk_disable(ARRAY_SIZE(aic31xx->supplies),
				       aic31xx->supplies);
		return ret;
	}

	return 0;
}
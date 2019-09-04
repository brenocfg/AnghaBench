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
struct tas6424_data {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAS6424_ALL_STATE_HIZ ; 
 int /*<<< orphan*/  TAS6424_CH_STATE_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tas6424_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas6424_power_off(struct snd_soc_component *component)
{
	struct tas6424_data *tas6424 = snd_soc_component_get_drvdata(component);
	int ret;

	snd_soc_component_write(component, TAS6424_CH_STATE_CTRL, TAS6424_ALL_STATE_HIZ);

	regcache_cache_only(tas6424->regmap, true);
	regcache_mark_dirty(tas6424->regmap);

	ret = regulator_bulk_disable(ARRAY_SIZE(tas6424->supplies),
				     tas6424->supplies);
	if (ret < 0) {
		dev_err(component->dev, "failed to disable supplies: %d\n", ret);
		return ret;
	}

	return 0;
}
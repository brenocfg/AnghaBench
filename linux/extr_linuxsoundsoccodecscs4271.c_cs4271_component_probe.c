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
struct snd_soc_component {TYPE_1__* dev; } ;
struct cs4271_private {int /*<<< orphan*/  regmap; int /*<<< orphan*/  enable_soft_reset; int /*<<< orphan*/  supplies; } ;
struct cs4271_platform_data {int amutec_eq_bmutec; int /*<<< orphan*/  enable_soft_reset; } ;
struct TYPE_2__ {struct cs4271_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4271_MODE2 ; 
 int CS4271_MODE2_CPEN ; 
 int CS4271_MODE2_MUTECAEQUB ; 
 int CS4271_MODE2_PDN ; 
 int /*<<< orphan*/  cs4271_reset (struct snd_soc_component*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs4271_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cs4271_component_probe(struct snd_soc_component *component)
{
	struct cs4271_private *cs4271 = snd_soc_component_get_drvdata(component);
	struct cs4271_platform_data *cs4271plat = component->dev->platform_data;
	int ret;
	bool amutec_eq_bmutec = false;

#ifdef CONFIG_OF
	if (of_match_device(cs4271_dt_ids, component->dev)) {
		if (of_get_property(component->dev->of_node,
				     "cirrus,amutec-eq-bmutec", NULL))
			amutec_eq_bmutec = true;

		if (of_get_property(component->dev->of_node,
				     "cirrus,enable-soft-reset", NULL))
			cs4271->enable_soft_reset = true;
	}
#endif

	ret = regulator_bulk_enable(ARRAY_SIZE(cs4271->supplies),
				    cs4271->supplies);
	if (ret < 0) {
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	if (cs4271plat) {
		amutec_eq_bmutec = cs4271plat->amutec_eq_bmutec;
		cs4271->enable_soft_reset = cs4271plat->enable_soft_reset;
	}

	/* Reset codec */
	cs4271_reset(component);

	ret = regcache_sync(cs4271->regmap);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				 CS4271_MODE2_PDN | CS4271_MODE2_CPEN,
				 CS4271_MODE2_PDN | CS4271_MODE2_CPEN);
	if (ret < 0)
		return ret;
	ret = regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				 CS4271_MODE2_PDN, 0);
	if (ret < 0)
		return ret;
	/* Power-up sequence requires 85 uS */
	udelay(85);

	if (amutec_eq_bmutec)
		regmap_update_bits(cs4271->regmap, CS4271_MODE2,
				   CS4271_MODE2_MUTECAEQUB,
				   CS4271_MODE2_MUTECAEQUB);

	return 0;
}
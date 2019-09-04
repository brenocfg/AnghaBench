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
struct snd_soc_component {int dummy; } ;
struct cs42l56_private {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS42L56_CLKCTL_1 ; 
 int /*<<< orphan*/  CS42L56_MCLK_DIS_MASK ; 
 int /*<<< orphan*/  CS42L56_PDN_ALL_MASK ; 
 int /*<<< orphan*/  CS42L56_PWRCTL_1 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct cs42l56_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs42l56_set_bias_level(struct snd_soc_component *component,
					enum snd_soc_bias_level level)
{
	struct cs42l56_private *cs42l56 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;
	case SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, CS42L56_CLKCTL_1,
				    CS42L56_MCLK_DIS_MASK, 0);
		snd_soc_component_update_bits(component, CS42L56_PWRCTL_1,
				    CS42L56_PDN_ALL_MASK, 0);
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			regcache_cache_only(cs42l56->regmap, false);
			regcache_sync(cs42l56->regmap);
			ret = regulator_bulk_enable(ARRAY_SIZE(cs42l56->supplies),
						    cs42l56->supplies);
			if (ret != 0) {
				dev_err(cs42l56->dev,
					"Failed to enable regulators: %d\n",
					ret);
				return ret;
			}
		}
		snd_soc_component_update_bits(component, CS42L56_PWRCTL_1,
				    CS42L56_PDN_ALL_MASK, 1);
		break;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, CS42L56_PWRCTL_1,
				    CS42L56_PDN_ALL_MASK, 1);
		snd_soc_component_update_bits(component, CS42L56_CLKCTL_1,
				    CS42L56_MCLK_DIS_MASK, 1);
		regcache_cache_only(cs42l56->regmap, true);
		regulator_bulk_disable(ARRAY_SIZE(cs42l56->supplies),
						    cs42l56->supplies);
		break;
	}

	return 0;
}
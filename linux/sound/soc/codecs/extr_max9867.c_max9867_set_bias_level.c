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
struct max9867_priv {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  MAX9867_PWRMAN ; 
 int /*<<< orphan*/  MAX9867_SHTDOWN ; 
#define  SND_SOC_BIAS_OFF 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int regcache_sync (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct max9867_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max9867_set_bias_level(struct snd_soc_component *component,
				  enum snd_soc_bias_level level)
{
	int err;
	struct max9867_priv *max9867 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			err = regcache_sync(max9867->regmap);
			if (err)
				return err;

			err = regmap_update_bits(max9867->regmap, MAX9867_PWRMAN,
						 MAX9867_SHTDOWN, MAX9867_SHTDOWN);
			if (err)
				return err;
		}
		break;
	case SND_SOC_BIAS_OFF:
		err = regmap_update_bits(max9867->regmap, MAX9867_PWRMAN,
					 MAX9867_SHTDOWN, 0);
		if (err)
			return err;

		regcache_mark_dirty(max9867->regmap);
		break;
	default:
		break;
	}

	return 0;
}
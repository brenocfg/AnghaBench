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
struct sta350_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  gpiod_nreset; int /*<<< orphan*/  gpiod_power_down; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  STA350_CONFF ; 
 int STA350_CONFF_EAPD ; 
 int STA350_CONFF_PWDN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct sta350_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sta350_cache_sync (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sta350_startup_sequence (struct sta350_priv*) ; 

__attribute__((used)) static int sta350_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct sta350_priv *sta350 = snd_soc_component_get_drvdata(component);
	int ret;

	dev_dbg(component->dev, "level = %d\n", level);
	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* Full power on */
		regmap_update_bits(sta350->regmap, STA350_CONFF,
				   STA350_CONFF_PWDN | STA350_CONFF_EAPD,
				   STA350_CONFF_PWDN | STA350_CONFF_EAPD);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(
				ARRAY_SIZE(sta350->supplies),
				sta350->supplies);
			if (ret < 0) {
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				return ret;
			}
			sta350_startup_sequence(sta350);
			sta350_cache_sync(component);
		}

		/* Power down */
		regmap_update_bits(sta350->regmap, STA350_CONFF,
				   STA350_CONFF_PWDN | STA350_CONFF_EAPD,
				   0);

		break;

	case SND_SOC_BIAS_OFF:
		/* The chip runs through the power down sequence for us */
		regmap_update_bits(sta350->regmap, STA350_CONFF,
				   STA350_CONFF_PWDN | STA350_CONFF_EAPD, 0);

		/* power down: low */
		if (sta350->gpiod_power_down)
			gpiod_set_value(sta350->gpiod_power_down, 0);

		if (sta350->gpiod_nreset)
			gpiod_set_value(sta350->gpiod_nreset, 0);

		regulator_bulk_disable(ARRAY_SIZE(sta350->supplies),
				       sta350->supplies);
		break;
	}
	return 0;
}
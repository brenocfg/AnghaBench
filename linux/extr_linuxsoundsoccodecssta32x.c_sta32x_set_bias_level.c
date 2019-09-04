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
struct sta32x_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  gpiod_nreset; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  STA32X_CONFF ; 
 int STA32X_CONFF_EAPD ; 
 int STA32X_CONFF_PWDN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct sta32x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sta32x_cache_sync (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sta32x_startup_sequence (struct sta32x_priv*) ; 
 int /*<<< orphan*/  sta32x_watchdog_start (struct sta32x_priv*) ; 
 int /*<<< orphan*/  sta32x_watchdog_stop (struct sta32x_priv*) ; 

__attribute__((used)) static int sta32x_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	int ret;
	struct sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "level = %d\n", level);
	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* Full power on */
		regmap_update_bits(sta32x->regmap, STA32X_CONFF,
				    STA32X_CONFF_PWDN | STA32X_CONFF_EAPD,
				    STA32X_CONFF_PWDN | STA32X_CONFF_EAPD);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			ret = regulator_bulk_enable(ARRAY_SIZE(sta32x->supplies),
						    sta32x->supplies);
			if (ret != 0) {
				dev_err(component->dev,
					"Failed to enable supplies: %d\n", ret);
				return ret;
			}

			sta32x_startup_sequence(sta32x);
			sta32x_cache_sync(component);
			sta32x_watchdog_start(sta32x);
		}

		/* Power down */
		regmap_update_bits(sta32x->regmap, STA32X_CONFF,
				   STA32X_CONFF_PWDN | STA32X_CONFF_EAPD,
				   0);

		break;

	case SND_SOC_BIAS_OFF:
		/* The chip runs through the power down sequence for us. */
		regmap_update_bits(sta32x->regmap, STA32X_CONFF,
				   STA32X_CONFF_PWDN | STA32X_CONFF_EAPD, 0);
		msleep(300);
		sta32x_watchdog_stop(sta32x);

		gpiod_set_value(sta32x->gpiod_nreset, 0);

		regulator_bulk_disable(ARRAY_SIZE(sta32x->supplies),
				       sta32x->supplies);
		break;
	}
	return 0;
}
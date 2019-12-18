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
struct rt5631_priv {int /*<<< orphan*/  regmap; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int RT5631_PWR_FAST_VREF_CTRL ; 
 int RT5631_PWR_MAIN_BIAS ; 
 int /*<<< orphan*/  RT5631_PWR_MANAG_ADD1 ; 
 int /*<<< orphan*/  RT5631_PWR_MANAG_ADD2 ; 
 int /*<<< orphan*/  RT5631_PWR_MANAG_ADD3 ; 
 int /*<<< orphan*/  RT5631_PWR_MANAG_ADD4 ; 
 int RT5631_PWR_MICBIAS1_VOL ; 
 int RT5631_PWR_MICBIAS2_VOL ; 
 int RT5631_PWR_VREF ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct rt5631_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt5631_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5631_priv *rt5631 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD2,
			RT5631_PWR_MICBIAS1_VOL | RT5631_PWR_MICBIAS2_VOL,
			RT5631_PWR_MICBIAS1_VOL | RT5631_PWR_MICBIAS2_VOL);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
				RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS,
				RT5631_PWR_VREF | RT5631_PWR_MAIN_BIAS);
			msleep(80);
			snd_soc_component_update_bits(component, RT5631_PWR_MANAG_ADD3,
				RT5631_PWR_FAST_VREF_CTRL,
				RT5631_PWR_FAST_VREF_CTRL);
			regcache_cache_only(rt5631->regmap, false);
			regcache_sync(rt5631->regmap);
		}
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_write(component, RT5631_PWR_MANAG_ADD1, 0x0000);
		snd_soc_component_write(component, RT5631_PWR_MANAG_ADD2, 0x0000);
		snd_soc_component_write(component, RT5631_PWR_MANAG_ADD3, 0x0000);
		snd_soc_component_write(component, RT5631_PWR_MANAG_ADD4, 0x0000);
		break;

	default:
		break;
	}

	return 0;
}
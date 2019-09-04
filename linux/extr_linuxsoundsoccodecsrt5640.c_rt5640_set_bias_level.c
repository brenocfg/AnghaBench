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
struct rt5640_priv {int /*<<< orphan*/  mclk; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT5640_DEPOP_M1 ; 
 int /*<<< orphan*/  RT5640_DEPOP_M2 ; 
 int /*<<< orphan*/  RT5640_DUMMY1 ; 
 int /*<<< orphan*/  RT5640_MICBIAS ; 
 int /*<<< orphan*/  RT5640_PWR_ANLG1 ; 
 int /*<<< orphan*/  RT5640_PWR_ANLG2 ; 
 int RT5640_PWR_BG ; 
 int /*<<< orphan*/  RT5640_PWR_DIG1 ; 
 int /*<<< orphan*/  RT5640_PWR_DIG2 ; 
 int RT5640_PWR_FV1 ; 
 int RT5640_PWR_FV2 ; 
 int RT5640_PWR_MB ; 
 int /*<<< orphan*/  RT5640_PWR_MIXER ; 
 int /*<<< orphan*/  RT5640_PWR_VOL ; 
 int RT5640_PWR_VREF1 ; 
 int RT5640_PWR_VREF2 ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt5640_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/*
		 * SND_SOC_BIAS_PREPARE is called while preparing for a
		 * transition to ON or away from ON. If current bias_level
		 * is SND_SOC_BIAS_ON, then it is preparing for a transition
		 * away from ON. Disable the clock in that case, otherwise
		 * enable it.
		 */
		if (IS_ERR(rt5640->mclk))
			break;

		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) {
			clk_disable_unprepare(rt5640->mclk);
		} else {
			ret = clk_prepare_enable(rt5640->mclk);
			if (ret)
				return ret;
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		if (SND_SOC_BIAS_OFF == snd_soc_component_get_bias_level(component)) {
			snd_soc_component_update_bits(component, RT5640_PWR_ANLG1,
				RT5640_PWR_VREF1 | RT5640_PWR_MB |
				RT5640_PWR_BG | RT5640_PWR_VREF2,
				RT5640_PWR_VREF1 | RT5640_PWR_MB |
				RT5640_PWR_BG | RT5640_PWR_VREF2);
			usleep_range(10000, 15000);
			snd_soc_component_update_bits(component, RT5640_PWR_ANLG1,
				RT5640_PWR_FV1 | RT5640_PWR_FV2,
				RT5640_PWR_FV1 | RT5640_PWR_FV2);
			snd_soc_component_update_bits(component, RT5640_DUMMY1,
						0x0301, 0x0301);
			snd_soc_component_update_bits(component, RT5640_MICBIAS,
						0x0030, 0x0030);
		}
		break;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_write(component, RT5640_DEPOP_M1, 0x0004);
		snd_soc_component_write(component, RT5640_DEPOP_M2, 0x1100);
		snd_soc_component_update_bits(component, RT5640_DUMMY1, 0x1, 0);
		snd_soc_component_write(component, RT5640_PWR_DIG1, 0x0000);
		snd_soc_component_write(component, RT5640_PWR_DIG2, 0x0000);
		snd_soc_component_write(component, RT5640_PWR_VOL, 0x0000);
		snd_soc_component_write(component, RT5640_PWR_MIXER, 0x0000);
		snd_soc_component_write(component, RT5640_PWR_ANLG1, 0x0000);
		snd_soc_component_write(component, RT5640_PWR_ANLG2, 0x0000);
		break;

	default:
		break;
	}

	return 0;
}
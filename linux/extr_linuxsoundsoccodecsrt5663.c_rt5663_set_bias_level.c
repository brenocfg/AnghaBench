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
struct rt5663_priv {int /*<<< orphan*/  jack_type; int /*<<< orphan*/  codec_ver; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_VER_1 ; 
 int RT5663_DIG_GATE_CTRL_DIS ; 
 int RT5663_DIG_GATE_CTRL_EN ; 
 int RT5663_DIG_GATE_CTRL_MASK ; 
 int /*<<< orphan*/  RT5663_DIG_MISC ; 
 int RT5663_EN_ANA_CLK_DET_AUTO ; 
 int RT5663_EN_ANA_CLK_DET_DIS ; 
 int RT5663_EN_ANA_CLK_DET_MASK ; 
 int /*<<< orphan*/  RT5663_PWR_ANLG_1 ; 
 int RT5663_PWR_CLK_DET_DIS ; 
 int RT5663_PWR_CLK_DET_EN ; 
 int RT5663_PWR_CLK_DET_MASK ; 
 int RT5663_PWR_FV1 ; 
 int RT5663_PWR_FV1_MASK ; 
 int RT5663_PWR_FV2 ; 
 int RT5663_PWR_FV2_MASK ; 
 int RT5663_PWR_MB ; 
 int RT5663_PWR_MB_MASK ; 
 int RT5663_PWR_VREF1 ; 
 int RT5663_PWR_VREF1_MASK ; 
 int RT5663_PWR_VREF2 ; 
 int RT5663_PWR_VREF2_MASK ; 
 int /*<<< orphan*/  RT5663_SIG_CLK_DET ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 struct rt5663_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt5663_set_bias_level(struct snd_soc_component *component,
			enum snd_soc_bias_level level)
{
	struct rt5663_priv *rt5663 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, RT5663_PWR_ANLG_1,
			RT5663_PWR_FV1_MASK | RT5663_PWR_FV2_MASK,
			RT5663_PWR_FV1 | RT5663_PWR_FV2);
		break;

	case SND_SOC_BIAS_PREPARE:
		if (rt5663->codec_ver == CODEC_VER_1) {
			snd_soc_component_update_bits(component, RT5663_DIG_MISC,
				RT5663_DIG_GATE_CTRL_MASK,
				RT5663_DIG_GATE_CTRL_EN);
			snd_soc_component_update_bits(component, RT5663_SIG_CLK_DET,
				RT5663_EN_ANA_CLK_DET_MASK |
				RT5663_PWR_CLK_DET_MASK,
				RT5663_EN_ANA_CLK_DET_AUTO |
				RT5663_PWR_CLK_DET_EN);
		}
		break;

	case SND_SOC_BIAS_STANDBY:
		if (rt5663->codec_ver == CODEC_VER_1)
			snd_soc_component_update_bits(component, RT5663_DIG_MISC,
				RT5663_DIG_GATE_CTRL_MASK,
				RT5663_DIG_GATE_CTRL_DIS);
		snd_soc_component_update_bits(component, RT5663_PWR_ANLG_1,
			RT5663_PWR_VREF1_MASK | RT5663_PWR_VREF2_MASK |
			RT5663_PWR_FV1_MASK | RT5663_PWR_FV2_MASK |
			RT5663_PWR_MB_MASK, RT5663_PWR_VREF1 |
			RT5663_PWR_VREF2 | RT5663_PWR_MB);
		usleep_range(10000, 10005);
		if (rt5663->codec_ver == CODEC_VER_1) {
			snd_soc_component_update_bits(component, RT5663_SIG_CLK_DET,
				RT5663_EN_ANA_CLK_DET_MASK |
				RT5663_PWR_CLK_DET_MASK,
				RT5663_EN_ANA_CLK_DET_DIS |
				RT5663_PWR_CLK_DET_DIS);
		}
		break;

	case SND_SOC_BIAS_OFF:
		if (rt5663->jack_type != SND_JACK_HEADSET)
			snd_soc_component_update_bits(component,
				RT5663_PWR_ANLG_1,
				RT5663_PWR_VREF1_MASK | RT5663_PWR_VREF2_MASK |
				RT5663_PWR_FV1 | RT5663_PWR_FV2 |
				RT5663_PWR_MB_MASK, 0);
		else
			snd_soc_component_update_bits(component,
				RT5663_PWR_ANLG_1,
				RT5663_PWR_FV1_MASK | RT5663_PWR_FV2_MASK,
				RT5663_PWR_FV1 | RT5663_PWR_FV2);
		break;

	default:
		break;
	}

	return 0;
}
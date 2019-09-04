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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct rt274_priv {int master; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT274_ADC_FORMAT ; 
 int /*<<< orphan*/  RT274_DAC_FORMAT ; 
 int /*<<< orphan*/  RT274_I2S_CTRL1 ; 
 int /*<<< orphan*/  RT274_I2S_FMT_I2S ; 
 int /*<<< orphan*/  RT274_I2S_FMT_LJ ; 
 int RT274_I2S_FMT_MASK ; 
 int /*<<< orphan*/  RT274_I2S_FMT_PCMA ; 
 int /*<<< orphan*/  RT274_I2S_FMT_PCMB ; 
 int /*<<< orphan*/  RT274_I2S_MODE_M ; 
 int RT274_I2S_MODE_MASK ; 
 int /*<<< orphan*/  RT274_I2S_MODE_S ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
#define  SND_SOC_DAIFMT_DSP_A 131 
#define  SND_SOC_DAIFMT_DSP_B 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 struct rt274_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt274_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_I2S_MODE_MASK, RT274_I2S_MODE_M);
		rt274->master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_I2S_MODE_MASK, RT274_I2S_MODE_S);
		rt274->master = false;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_I2S);
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_LJ);
		break;
	case SND_SOC_DAIFMT_DSP_A:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_PCMA);
		break;
	case SND_SOC_DAIFMT_DSP_B:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_PCMB);
		break;
	default:
		return -EINVAL;
	}
	/* bit 15 Stream Type 0:PCM 1:Non-PCM */
	snd_soc_component_update_bits(component, RT274_DAC_FORMAT, 0x8000, 0);
	snd_soc_component_update_bits(component, RT274_ADC_FORMAT, 0x8000, 0);

	return 0;
}
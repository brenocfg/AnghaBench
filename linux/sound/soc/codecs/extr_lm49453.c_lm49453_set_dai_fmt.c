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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int LM49453_AUDIO_PORT1_BASIC_CLK_MS ; 
 int LM49453_AUDIO_PORT1_BASIC_FMT_MASK ; 
 int LM49453_AUDIO_PORT1_BASIC_SYNC_MS ; 
 int /*<<< orphan*/  LM49453_P0_AUDIO_PORT1_BASIC_REG ; 
 int /*<<< orphan*/  LM49453_P0_AUDIO_PORT1_RX_MSB_REG ; 
#define  SND_SOC_DAIFMT_CBM_CFM 134 
#define  SND_SOC_DAIFMT_CBM_CFS 133 
#define  SND_SOC_DAIFMT_CBS_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
#define  SND_SOC_DAIFMT_DSP_A 130 
#define  SND_SOC_DAIFMT_DSP_B 129 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm49453_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;

	u16 aif_val;
	int mode = 0;
	int clk_phase = 0;
	int clk_shift = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		aif_val = 0;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		aif_val = LM49453_AUDIO_PORT1_BASIC_SYNC_MS;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		aif_val = LM49453_AUDIO_PORT1_BASIC_CLK_MS;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		aif_val = LM49453_AUDIO_PORT1_BASIC_CLK_MS |
			  LM49453_AUDIO_PORT1_BASIC_SYNC_MS;
		break;
	default:
		return -EINVAL;
	}


	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_DSP_A:
		mode = 1;
		clk_phase = (1 << 5);
		clk_shift = 1;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		mode = 1;
		clk_phase = (1 << 5);
		clk_shift = 0;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, LM49453_P0_AUDIO_PORT1_BASIC_REG,
			    LM49453_AUDIO_PORT1_BASIC_FMT_MASK|BIT(0)|BIT(5),
			    (aif_val | mode | clk_phase));

	snd_soc_component_write(component, LM49453_P0_AUDIO_PORT1_RX_MSB_REG, clk_shift);

	return 0;
}
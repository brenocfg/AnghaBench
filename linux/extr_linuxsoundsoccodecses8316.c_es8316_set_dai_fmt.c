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
typedef  int u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ES8316_CLKMGR_CLKSW ; 
 int ES8316_CLKMGR_CLKSW_BCLK_ON ; 
 int ES8316_CLKMGR_CLKSW_MCLK_ON ; 
 int /*<<< orphan*/  ES8316_SERDATA1 ; 
 int ES8316_SERDATA1_BCLK_INV ; 
 int ES8316_SERDATA1_MASTER ; 
 int ES8316_SERDATA2_ADCLRP ; 
 int ES8316_SERDATA2_FMT_MASK ; 
 int /*<<< orphan*/  ES8316_SERDATA_ADC ; 
 int /*<<< orphan*/  ES8316_SERDATA_DAC ; 
 unsigned int SND_SOC_DAIFMT_CBS_CFS ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
 unsigned int SND_SOC_DAIFMT_I2S ; 
#define  SND_SOC_DAIFMT_IB_IF 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int es8316_set_dai_fmt(struct snd_soc_dai *codec_dai,
			      unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	u8 serdata1 = 0;
	u8 serdata2 = 0;
	u8 clksw;
	u8 mask;

	if ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) {
		dev_err(component->dev, "Codec driver only supports slave mode\n");
		return -EINVAL;
	}

	if ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_I2S) {
		dev_err(component->dev, "Codec driver only supports I2S format\n");
		return -EINVAL;
	}

	/* Clock inversion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		serdata1 |= ES8316_SERDATA1_BCLK_INV;
		serdata2 |= ES8316_SERDATA2_ADCLRP;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		serdata1 |= ES8316_SERDATA1_BCLK_INV;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		serdata2 |= ES8316_SERDATA2_ADCLRP;
		break;
	default:
		return -EINVAL;
	}

	mask = ES8316_SERDATA1_MASTER | ES8316_SERDATA1_BCLK_INV;
	snd_soc_component_update_bits(component, ES8316_SERDATA1, mask, serdata1);

	mask = ES8316_SERDATA2_FMT_MASK | ES8316_SERDATA2_ADCLRP;
	snd_soc_component_update_bits(component, ES8316_SERDATA_ADC, mask, serdata2);
	snd_soc_component_update_bits(component, ES8316_SERDATA_DAC, mask, serdata2);

	/* Enable BCLK and MCLK inputs in slave mode */
	clksw = ES8316_CLKMGR_CLKSW_MCLK_ON | ES8316_CLKMGR_CLKSW_BCLK_ON;
	snd_soc_component_update_bits(component, ES8316_CLKMGR_CLKSW, clksw, clksw);

	return 0;
}
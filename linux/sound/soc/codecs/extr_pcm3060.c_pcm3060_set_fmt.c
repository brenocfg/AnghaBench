#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct pcm3060_priv {int /*<<< orphan*/  regmap; TYPE_1__* dai; } ;
struct TYPE_2__ {int is_master; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCM3060_DAI_ID_DAC ; 
 unsigned int PCM3060_REG67 ; 
 unsigned int PCM3060_REG72 ; 
 unsigned int PCM3060_REG_FMT_I2S ; 
 unsigned int PCM3060_REG_FMT_LJ ; 
 unsigned int PCM3060_REG_FMT_RJ ; 
 int /*<<< orphan*/  PCM3060_REG_MASK_FMT ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 unsigned int SND_SOC_DAIFMT_NB_NF ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 struct pcm3060_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm3060_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *comp = dai->component;
	struct pcm3060_priv *priv = snd_soc_component_get_drvdata(comp);
	unsigned int reg;
	unsigned int val;

	if ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF) {
		dev_err(comp->dev, "unsupported DAI polarity: 0x%x\n", fmt);
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		priv->dai[dai->id].is_master = true;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		priv->dai[dai->id].is_master = false;
		break;
	default:
		dev_err(comp->dev, "unsupported DAI master mode: 0x%x\n", fmt);
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		val = PCM3060_REG_FMT_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		val = PCM3060_REG_FMT_RJ;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		val = PCM3060_REG_FMT_LJ;
		break;
	default:
		dev_err(comp->dev, "unsupported DAI format: 0x%x\n", fmt);
		return -EINVAL;
	}

	if (dai->id == PCM3060_DAI_ID_DAC)
		reg = PCM3060_REG67;
	else
		reg = PCM3060_REG72;

	regmap_update_bits(priv->regmap, reg, PCM3060_REG_MASK_FMT, val);

	return 0;
}
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
struct snd_soc_component {int dummy; } ;
struct max9867_priv {int master; int dsp_a; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX9867_BCI_MODE ; 
 int MAX9867_I2S_DLY ; 
 int /*<<< orphan*/  MAX9867_IFC1A ; 
 int /*<<< orphan*/  MAX9867_IFC1B ; 
 int MAX9867_IFC1B_48X ; 
 int MAX9867_MASTER ; 
 int MAX9867_SDOUT_HIZ ; 
 int MAX9867_TDM_MODE ; 
 int MAX9867_WCI_MODE ; 
#define  SND_SOC_DAIFMT_CBM_CFM 135 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
#define  SND_SOC_DAIFMT_DSP_A 133 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 132 
#define  SND_SOC_DAIFMT_IB_IF 131 
#define  SND_SOC_DAIFMT_IB_NF 130 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct max9867_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max9867_dai_set_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct max9867_priv *max9867 = snd_soc_component_get_drvdata(component);
	u8 iface1A, iface1B;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		max9867->master = true;
		iface1A = MAX9867_MASTER;
		iface1B = MAX9867_IFC1B_48X;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		max9867->master = false;
		iface1A = iface1B = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		max9867->dsp_a = false;
		iface1A |= MAX9867_I2S_DLY;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		max9867->dsp_a = true;
		iface1A |= MAX9867_TDM_MODE | MAX9867_SDOUT_HIZ;
		break;
	default:
		return -EINVAL;
	}

	/* Clock inversion bits, BCI and WCI */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		iface1A |= MAX9867_WCI_MODE | MAX9867_BCI_MODE;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		iface1A |= MAX9867_BCI_MODE;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		iface1A |= MAX9867_WCI_MODE;
		break;
	default:
		return -EINVAL;
	}

	regmap_write(max9867->regmap, MAX9867_IFC1A, iface1A);
	regmap_write(max9867->regmap, MAX9867_IFC1B, iface1B);

	return 0;
}
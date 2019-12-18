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
struct snd_soc_dai {TYPE_1__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct madera_priv {struct madera* madera; } ;
struct madera {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int base; } ;

/* Variables and functions */
 int EINVAL ; 
 int MADERA_AIF1RX_LRCLK_INV ; 
 int MADERA_AIF1RX_LRCLK_MSTR ; 
 int MADERA_AIF1TX_LRCLK_INV ; 
 int MADERA_AIF1TX_LRCLK_MSTR ; 
 int MADERA_AIF1_BCLK_INV ; 
 int MADERA_AIF1_BCLK_MSTR ; 
 int MADERA_AIF1_FMT_MASK ; 
 scalar_t__ MADERA_AIF_BCLK_CTRL ; 
 scalar_t__ MADERA_AIF_FORMAT ; 
 scalar_t__ MADERA_AIF_RX_PIN_CTRL ; 
 scalar_t__ MADERA_AIF_TX_PIN_CTRL ; 
 int MADERA_FMT_DSP_MODE_A ; 
 int MADERA_FMT_DSP_MODE_B ; 
 int MADERA_FMT_I2S_MODE ; 
 int MADERA_FMT_LEFT_JUSTIFIED_MODE ; 
#define  SND_SOC_DAIFMT_CBM_CFM 139 
#define  SND_SOC_DAIFMT_CBM_CFS 138 
#define  SND_SOC_DAIFMT_CBS_CFM 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_A 135 
#define  SND_SOC_DAIFMT_DSP_B 134 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  madera_aif_err (struct snd_soc_dai*,char*,...) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int madera_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;
	int lrclk, bclk, mode, base;

	base = dai->driver->base;

	lrclk = 0;
	bclk = 0;

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		mode = MADERA_FMT_DSP_MODE_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		if ((fmt & SND_SOC_DAIFMT_MASTER_MASK) !=
		    SND_SOC_DAIFMT_CBM_CFM) {
			madera_aif_err(dai, "DSP_B not valid in slave mode\n");
			return -EINVAL;
		}
		mode = MADERA_FMT_DSP_MODE_B;
		break;
	case SND_SOC_DAIFMT_I2S:
		mode = MADERA_FMT_I2S_MODE;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		if ((fmt & SND_SOC_DAIFMT_MASTER_MASK) !=
		    SND_SOC_DAIFMT_CBM_CFM) {
			madera_aif_err(dai, "LEFT_J not valid in slave mode\n");
			return -EINVAL;
		}
		mode = MADERA_FMT_LEFT_JUSTIFIED_MODE;
		break;
	default:
		madera_aif_err(dai, "Unsupported DAI format %d\n",
			       fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		lrclk |= MADERA_AIF1TX_LRCLK_MSTR;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		bclk |= MADERA_AIF1_BCLK_MSTR;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		bclk |= MADERA_AIF1_BCLK_MSTR;
		lrclk |= MADERA_AIF1TX_LRCLK_MSTR;
		break;
	default:
		madera_aif_err(dai, "Unsupported master mode %d\n",
			       fmt & SND_SOC_DAIFMT_MASTER_MASK);
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		bclk |= MADERA_AIF1_BCLK_INV;
		lrclk |= MADERA_AIF1TX_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		bclk |= MADERA_AIF1_BCLK_INV;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		lrclk |= MADERA_AIF1TX_LRCLK_INV;
		break;
	default:
		madera_aif_err(dai, "Unsupported invert mode %d\n",
			       fmt & SND_SOC_DAIFMT_INV_MASK);
		return -EINVAL;
	}

	regmap_update_bits(madera->regmap, base + MADERA_AIF_BCLK_CTRL,
			   MADERA_AIF1_BCLK_INV | MADERA_AIF1_BCLK_MSTR,
			   bclk);
	regmap_update_bits(madera->regmap, base + MADERA_AIF_TX_PIN_CTRL,
			   MADERA_AIF1TX_LRCLK_INV | MADERA_AIF1TX_LRCLK_MSTR,
			   lrclk);
	regmap_update_bits(madera->regmap, base + MADERA_AIF_RX_PIN_CTRL,
			   MADERA_AIF1RX_LRCLK_INV | MADERA_AIF1RX_LRCLK_MSTR,
			   lrclk);
	regmap_update_bits(madera->regmap, base + MADERA_AIF_FORMAT,
			   MADERA_AIF1_FMT_MASK, mode);

	return 0;
}
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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct cs53l30_private {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS53L30_ASPCFG_CTL ; 
 int /*<<< orphan*/  CS53L30_ASP_CTL1 ; 
 int CS53L30_ASP_MS ; 
 int CS53L30_ASP_SCLK_INV ; 
 int CS53L30_ASP_TDM_PDN ; 
 int CS53L30_SHIFT_LEFT ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 133 
#define  SND_SOC_DAIFMT_CBS_CFS 132 
#define  SND_SOC_DAIFMT_DSP_A 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_IB_IF 129 
#define  SND_SOC_DAIFMT_IB_NF 128 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct cs53l30_private* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs53l30_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct cs53l30_private *priv = snd_soc_component_get_drvdata(dai->component);
	u8 aspcfg = 0, aspctl1 = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		aspcfg |= CS53L30_ASP_MS;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	/* DAI mode */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* Set TDM_PDN to turn off TDM mode -- Reset default */
		aspctl1 |= CS53L30_ASP_TDM_PDN;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		/*
		 * Clear TDM_PDN to turn on TDM mode; Use ASP_SCLK_INV = 0
		 * with SHIFT_LEFT = 1 combination as Figure 4-13 shows in
		 * the CS53L30 datasheet
		 */
		aspctl1 |= CS53L30_SHIFT_LEFT;
		break;
	default:
		return -EINVAL;
	}

	/* Check to see if the SCLK is inverted */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
	case SND_SOC_DAIFMT_IB_IF:
		aspcfg ^= CS53L30_ASP_SCLK_INV;
		break;
	default:
		break;
	}

	regmap_update_bits(priv->regmap, CS53L30_ASPCFG_CTL,
			   CS53L30_ASP_MS | CS53L30_ASP_SCLK_INV, aspcfg);

	regmap_update_bits(priv->regmap, CS53L30_ASP_CTL1,
			   CS53L30_ASP_TDM_PDN | CS53L30_SHIFT_LEFT, aspctl1);

	return 0;
}
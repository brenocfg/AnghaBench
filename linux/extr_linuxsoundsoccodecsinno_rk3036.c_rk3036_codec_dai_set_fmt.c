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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INNO_R01 ; 
 unsigned int INNO_R01_I2SMODE_MASTER ; 
 int INNO_R01_I2SMODE_MSK ; 
 unsigned int INNO_R01_I2SMODE_SLAVE ; 
 unsigned int INNO_R01_PINDIR_IN_SLAVE ; 
 int INNO_R01_PINDIR_MSK ; 
 unsigned int INNO_R01_PINDIR_OUT_MASTER ; 
 int /*<<< orphan*/  INNO_R02 ; 
 unsigned int INNO_R02_DACM_I2S ; 
 unsigned int INNO_R02_DACM_LJM ; 
 int INNO_R02_DACM_MSK ; 
 unsigned int INNO_R02_DACM_PCM ; 
 unsigned int INNO_R02_DACM_RJM ; 
 int INNO_R02_LRCP_MSK ; 
 unsigned int INNO_R02_LRCP_NORMAL ; 
 unsigned int INNO_R02_LRCP_REVERSAL ; 
 int /*<<< orphan*/  INNO_R03 ; 
 int INNO_R03_BCP_MSK ; 
 unsigned int INNO_R03_BCP_NORMAL ; 
 unsigned int INNO_R03_BCP_REVERSAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_A 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int rk3036_codec_dai_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	unsigned int reg01_val = 0,  reg02_val = 0, reg03_val = 0;

	dev_dbg(component->dev, "rk3036_codec dai set fmt : %08x\n", fmt);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		reg01_val |= INNO_R01_PINDIR_IN_SLAVE |
			     INNO_R01_I2SMODE_SLAVE;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		reg01_val |= INNO_R01_PINDIR_OUT_MASTER |
			     INNO_R01_I2SMODE_MASTER;
		break;
	default:
		dev_err(component->dev, "invalid fmt\n");
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		reg02_val |= INNO_R02_DACM_PCM;
		break;
	case SND_SOC_DAIFMT_I2S:
		reg02_val |= INNO_R02_DACM_I2S;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		reg02_val |= INNO_R02_DACM_RJM;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		reg02_val |= INNO_R02_DACM_LJM;
		break;
	default:
		dev_err(component->dev, "set dai format failed\n");
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		reg02_val |= INNO_R02_LRCP_NORMAL;
		reg03_val |= INNO_R03_BCP_NORMAL;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		reg02_val |= INNO_R02_LRCP_REVERSAL;
		reg03_val |= INNO_R03_BCP_REVERSAL;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg02_val |= INNO_R02_LRCP_REVERSAL;
		reg03_val |= INNO_R03_BCP_NORMAL;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		reg02_val |= INNO_R02_LRCP_NORMAL;
		reg03_val |= INNO_R03_BCP_REVERSAL;
		break;
	default:
		dev_err(component->dev, "set dai format failed\n");
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, INNO_R01, INNO_R01_I2SMODE_MSK |
			    INNO_R01_PINDIR_MSK, reg01_val);
	snd_soc_component_update_bits(component, INNO_R02, INNO_R02_LRCP_MSK |
			    INNO_R02_DACM_MSK, reg02_val);
	snd_soc_component_update_bits(component, INNO_R03, INNO_R03_BCP_MSK, reg03_val);

	return 0;
}
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
struct stm32_sai_sub_data {int master; unsigned int fmt; int /*<<< orphan*/  regmap; scalar_t__ sync; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SAI_FREE_PROTOCOL ; 
 int /*<<< orphan*/  SAI_SPDIF_PROTOCOL ; 
 int SAI_XCR1_CKSTR ; 
 int SAI_XCR1_NODIV ; 
 int SAI_XCR1_PRTCFG_MASK ; 
 int SAI_XCR1_PRTCFG_SET (int /*<<< orphan*/ ) ; 
 int SAI_XCR1_SLAVE ; 
 int SAI_XFRCR_FSDEF ; 
 int SAI_XFRCR_FSOFF ; 
 int SAI_XFRCR_FSPOL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LSB 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_MSB 130 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  STM_SAI_FRCR_REGX ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_sai_set_dai_fmt(struct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int cr1, frcr = 0;
	int cr1_mask, frcr_mask = 0;
	int ret;

	dev_dbg(cpu_dai->dev, "fmt %x\n", fmt);

	/* Do not generate master by default */
	cr1 = SAI_XCR1_NODIV;
	cr1_mask = SAI_XCR1_NODIV;

	cr1_mask |= SAI_XCR1_PRTCFG_MASK;
	if (STM_SAI_PROTOCOL_IS_SPDIF(sai)) {
		cr1 |= SAI_XCR1_PRTCFG_SET(SAI_SPDIF_PROTOCOL);
		goto conf_update;
	}

	cr1 |= SAI_XCR1_PRTCFG_SET(SAI_FREE_PROTOCOL);

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	/* SCK active high for all protocols */
	case SND_SOC_DAIFMT_I2S:
		cr1 |= SAI_XCR1_CKSTR;
		frcr |= SAI_XFRCR_FSOFF | SAI_XFRCR_FSDEF;
		break;
	/* Left justified */
	case SND_SOC_DAIFMT_MSB:
		frcr |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSDEF;
		break;
	/* Right justified */
	case SND_SOC_DAIFMT_LSB:
		frcr |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSDEF;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		frcr |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSOFF;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		frcr |= SAI_XFRCR_FSPOL;
		break;
	default:
		dev_err(cpu_dai->dev, "Unsupported protocol %#x\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		return -EINVAL;
	}

	cr1_mask |= SAI_XCR1_CKSTR;
	frcr_mask |= SAI_XFRCR_FSPOL | SAI_XFRCR_FSOFF |
		     SAI_XFRCR_FSDEF;

	/* DAI clock strobing. Invert setting previously set */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		cr1 ^= SAI_XCR1_CKSTR;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		frcr ^= SAI_XFRCR_FSPOL;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		/* Invert fs & sck */
		cr1 ^= SAI_XCR1_CKSTR;
		frcr ^= SAI_XFRCR_FSPOL;
		break;
	default:
		dev_err(cpu_dai->dev, "Unsupported strobing %#x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		return -EINVAL;
	}
	cr1_mask |= SAI_XCR1_CKSTR;
	frcr_mask |= SAI_XFRCR_FSPOL;

	regmap_update_bits(sai->regmap, STM_SAI_FRCR_REGX, frcr_mask, frcr);

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		/* codec is master */
		cr1 |= SAI_XCR1_SLAVE;
		sai->master = false;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		sai->master = true;
		break;
	default:
		dev_err(cpu_dai->dev, "Unsupported mode %#x\n",
			fmt & SND_SOC_DAIFMT_MASTER_MASK);
		return -EINVAL;
	}

	/* Set slave mode if sub-block is synchronized with another SAI */
	if (sai->sync) {
		dev_dbg(cpu_dai->dev, "Synchronized SAI configured as slave\n");
		cr1 |= SAI_XCR1_SLAVE;
		sai->master = false;
	}

	cr1_mask |= SAI_XCR1_SLAVE;

conf_update:
	ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX, cr1_mask, cr1);
	if (ret < 0) {
		dev_err(cpu_dai->dev, "Failed to update CR1 register\n");
		return ret;
	}

	sai->fmt = fmt;

	return 0;
}
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
typedef  int u32 ;
struct stm32_i2s_data {unsigned int fmt; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ms_flg; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2S_CGFR_CKPOL ; 
 int I2S_CGFR_I2SCFG_MASK ; 
 int I2S_CGFR_I2SSTD_MASK ; 
 int I2S_CGFR_I2SSTD_SET (int /*<<< orphan*/ ) ; 
 int I2S_CGFR_WSINV ; 
 int /*<<< orphan*/  I2S_MS_MASTER ; 
 int /*<<< orphan*/  I2S_MS_SLAVE ; 
 int /*<<< orphan*/  I2S_STD_DSP ; 
 int /*<<< orphan*/  I2S_STD_I2S ; 
 int /*<<< orphan*/  I2S_STD_LEFT_J ; 
 int /*<<< orphan*/  I2S_STD_RIGHT_J ; 
#define  SND_SOC_DAIFMT_CBM_CFM 137 
#define  SND_SOC_DAIFMT_CBS_CFS 136 
#define  SND_SOC_DAIFMT_DSP_A 135 
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
 int /*<<< orphan*/  STM32_I2S_CGFR_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_i2s_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_i2s_set_dai_fmt(struct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	struct stm32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	u32 cgfr;
	u32 cgfr_mask =  I2S_CGFR_I2SSTD_MASK | I2S_CGFR_CKPOL |
			 I2S_CGFR_WSINV | I2S_CGFR_I2SCFG_MASK;

	dev_dbg(cpu_dai->dev, "fmt %x\n", fmt);

	/*
	 * winv = 0 : default behavior (high/low) for all standards
	 * ckpol = 0 for all standards.
	 */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_I2S);
		break;
	case SND_SOC_DAIFMT_MSB:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_LEFT_J);
		break;
	case SND_SOC_DAIFMT_LSB:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_RIGHT_J);
		break;
	case SND_SOC_DAIFMT_DSP_A:
		cgfr = I2S_CGFR_I2SSTD_SET(I2S_STD_DSP);
		break;
	/* DSP_B not mapped on I2S PCM long format. 1 bit offset does not fit */
	default:
		dev_err(cpu_dai->dev, "Unsupported protocol %#x\n",
			fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		return -EINVAL;
	}

	/* DAI clock strobing */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		cgfr |= I2S_CGFR_CKPOL;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		cgfr |= I2S_CGFR_WSINV;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		cgfr |= I2S_CGFR_CKPOL;
		cgfr |= I2S_CGFR_WSINV;
		break;
	default:
		dev_err(cpu_dai->dev, "Unsupported strobing %#x\n",
			fmt & SND_SOC_DAIFMT_INV_MASK);
		return -EINVAL;
	}

	/* DAI clock master masks */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		i2s->ms_flg = I2S_MS_SLAVE;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		i2s->ms_flg = I2S_MS_MASTER;
		break;
	default:
		dev_err(cpu_dai->dev, "Unsupported mode %#x\n",
			fmt & SND_SOC_DAIFMT_MASTER_MASK);
		return -EINVAL;
	}

	i2s->fmt = fmt;
	return regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
				  cgfr_mask, cgfr);
}
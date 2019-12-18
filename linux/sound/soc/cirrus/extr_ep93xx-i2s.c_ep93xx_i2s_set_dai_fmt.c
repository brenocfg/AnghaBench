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
struct snd_soc_dai {int dummy; } ;
struct ep93xx_i2s_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int EP93XX_I2S_CLKCFG_CKP ; 
 unsigned int EP93XX_I2S_CLKCFG_LRS ; 
 unsigned int EP93XX_I2S_CLKCFG_MASTER ; 
 unsigned int EP93XX_I2S_CLKCFG_REL ; 
 int /*<<< orphan*/  EP93XX_I2S_RXCLKCFG ; 
 int /*<<< orphan*/  EP93XX_I2S_RXLINCTRLDATA ; 
 unsigned int EP93XX_I2S_RXLINCTRLDATA_R_JUST ; 
 int /*<<< orphan*/  EP93XX_I2S_TXCLKCFG ; 
 int /*<<< orphan*/  EP93XX_I2S_TXLINCTRLDATA ; 
 unsigned int EP93XX_I2S_TXLINCTRLDATA_R_JUST ; 
#define  SND_SOC_DAIFMT_CBM_CFM 136 
#define  SND_SOC_DAIFMT_CBS_CFS 135 
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
 unsigned int ep93xx_i2s_read_reg (struct ep93xx_i2s_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_i2s_write_reg (struct ep93xx_i2s_info*,int /*<<< orphan*/ ,unsigned int) ; 
 struct ep93xx_i2s_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int ep93xx_i2s_set_dai_fmt(struct snd_soc_dai *cpu_dai,
				  unsigned int fmt)
{
	struct ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned int clk_cfg;
	unsigned int txlin_ctrl = 0;
	unsigned int rxlin_ctrl = 0;

	clk_cfg  = ep93xx_i2s_read_reg(info, EP93XX_I2S_RXCLKCFG);

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		clk_cfg |= EP93XX_I2S_CLKCFG_REL;
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		clk_cfg &= ~EP93XX_I2S_CLKCFG_REL;
		break;

	case SND_SOC_DAIFMT_RIGHT_J:
		clk_cfg &= ~EP93XX_I2S_CLKCFG_REL;
		rxlin_ctrl |= EP93XX_I2S_RXLINCTRLDATA_R_JUST;
		txlin_ctrl |= EP93XX_I2S_TXLINCTRLDATA_R_JUST;
		break;

	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* CPU is master */
		clk_cfg |= EP93XX_I2S_CLKCFG_MASTER;
		break;

	case SND_SOC_DAIFMT_CBM_CFM:
		/* Codec is master */
		clk_cfg &= ~EP93XX_I2S_CLKCFG_MASTER;
		break;

	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/* Negative bit clock, lrclk low on left word */
		clk_cfg &= ~(EP93XX_I2S_CLKCFG_CKP | EP93XX_I2S_CLKCFG_LRS);
		break;

	case SND_SOC_DAIFMT_NB_IF:
		/* Negative bit clock, lrclk low on right word */
		clk_cfg &= ~EP93XX_I2S_CLKCFG_CKP;
		clk_cfg |= EP93XX_I2S_CLKCFG_LRS;
		break;

	case SND_SOC_DAIFMT_IB_NF:
		/* Positive bit clock, lrclk low on left word */
		clk_cfg |= EP93XX_I2S_CLKCFG_CKP;
		clk_cfg &= ~EP93XX_I2S_CLKCFG_LRS;
		break;

	case SND_SOC_DAIFMT_IB_IF:
		/* Positive bit clock, lrclk low on right word */
		clk_cfg |= EP93XX_I2S_CLKCFG_CKP | EP93XX_I2S_CLKCFG_LRS;
		break;
	}

	/* Write new register values */
	ep93xx_i2s_write_reg(info, EP93XX_I2S_RXCLKCFG, clk_cfg);
	ep93xx_i2s_write_reg(info, EP93XX_I2S_TXCLKCFG, clk_cfg);
	ep93xx_i2s_write_reg(info, EP93XX_I2S_RXLINCTRLDATA, rxlin_ctrl);
	ep93xx_i2s_write_reg(info, EP93XX_I2S_TXLINCTRLDATA, txlin_ctrl);
	return 0;
}
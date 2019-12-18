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
struct snd_soc_dai {int dummy; } ;
struct davinci_mcasp {int bclk_master; unsigned int dai_fmt; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLKRE ; 
 int /*<<< orphan*/  ACLKRPOL ; 
 int /*<<< orphan*/  ACLKXE ; 
 int /*<<< orphan*/  ACLKXPOL ; 
 int /*<<< orphan*/  AFSRE ; 
 int /*<<< orphan*/  AFSXE ; 
 int /*<<< orphan*/  DAVINCI_MCASP_ACLKRCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_ACLKXCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXFMCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXFMT_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXFMCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXFMT_REG ; 
 int EINVAL ; 
 int /*<<< orphan*/  FSRDLY (int) ; 
 int /*<<< orphan*/  FSRDUR ; 
 int /*<<< orphan*/  FSRPOL ; 
 int /*<<< orphan*/  FSXDLY (int) ; 
 int /*<<< orphan*/  FSXDUR ; 
 int /*<<< orphan*/  FSXPOL ; 
 int /*<<< orphan*/  PIN_BIT_ACLKR ; 
 int /*<<< orphan*/  PIN_BIT_ACLKX ; 
 int /*<<< orphan*/  PIN_BIT_AFSR ; 
 int /*<<< orphan*/  PIN_BIT_AFSX ; 
#define  SND_SOC_DAIFMT_AC97 141 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBM_CFS 139 
#define  SND_SOC_DAIFMT_CBS_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
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
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_mod_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_bits (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct davinci_mcasp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int davinci_mcasp_set_dai_fmt(struct snd_soc_dai *cpu_dai,
					 unsigned int fmt)
{
	struct davinci_mcasp *mcasp = snd_soc_dai_get_drvdata(cpu_dai);
	int ret = 0;
	u32 data_delay;
	bool fs_pol_rising;
	bool inv_fs = false;

	if (!fmt)
		return 0;

	pm_runtime_get_sync(mcasp->dev);
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* 1st data bit occur one ACLK cycle after the frame sync */
		data_delay = 1;
		break;
	case SND_SOC_DAIFMT_DSP_B:
	case SND_SOC_DAIFMT_AC97:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* No delay after FS */
		data_delay = 0;
		break;
	case SND_SOC_DAIFMT_I2S:
		/* configure a full-word SYNC pulse (LRCLK) */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* 1st data bit occur one ACLK cycle after the frame sync */
		data_delay = 1;
		/* FS need to be inverted */
		inv_fs = true;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
	case SND_SOC_DAIFMT_LEFT_J:
		/* configure a full-word SYNC pulse (LRCLK) */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXDUR);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRDUR);
		/* No delay after FS */
		data_delay = 0;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	mcasp_mod_bits(mcasp, DAVINCI_MCASP_TXFMT_REG, FSXDLY(data_delay),
		       FSXDLY(3));
	mcasp_mod_bits(mcasp, DAVINCI_MCASP_RXFMT_REG, FSRDLY(data_delay),
		       FSRDLY(3));

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* codec is clock and frame slave */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		set_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		set_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		set_bit(PIN_BIT_AFSX, &mcasp->pdir);
		set_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 1;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		/* codec is clock slave and frame master */
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		set_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		set_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		clear_bit(PIN_BIT_AFSX, &mcasp->pdir);
		clear_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		/* codec is clock master and frame slave */
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		clear_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		clear_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		set_bit(PIN_BIT_AFSX, &mcasp->pdir);
		set_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 0;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		/* codec is clock and frame master */
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, AFSXE);

		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRE);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, AFSRE);

		/* BCLK */
		clear_bit(PIN_BIT_ACLKX, &mcasp->pdir);
		clear_bit(PIN_BIT_ACLKR, &mcasp->pdir);
		/* Frame Sync */
		clear_bit(PIN_BIT_AFSX, &mcasp->pdir);
		clear_bit(PIN_BIT_AFSR, &mcasp->pdir);

		mcasp->bclk_master = 0;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = true;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = false;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = false;
		break;
	case SND_SOC_DAIFMT_NB_NF:
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKXCTL_REG, ACLKXPOL);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_ACLKRCTL_REG, ACLKRPOL);
		fs_pol_rising = true;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	if (inv_fs)
		fs_pol_rising = !fs_pol_rising;

	if (fs_pol_rising) {
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXPOL);
		mcasp_clr_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRPOL);
	} else {
		mcasp_set_bits(mcasp, DAVINCI_MCASP_TXFMCTL_REG, FSXPOL);
		mcasp_set_bits(mcasp, DAVINCI_MCASP_RXFMCTL_REG, FSRPOL);
	}

	mcasp->dai_fmt = fmt;
out:
	pm_runtime_put(mcasp->dev);
	return ret;
}
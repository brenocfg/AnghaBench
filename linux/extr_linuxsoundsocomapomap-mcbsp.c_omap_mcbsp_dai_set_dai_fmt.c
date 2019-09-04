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
struct snd_soc_dai {int dummy; } ;
struct omap_mcbsp_reg_cfg {int spcr2; int xccr; int rccr; int pcr0; int /*<<< orphan*/  srgr2; int /*<<< orphan*/  xcr2; int /*<<< orphan*/  rcr2; int /*<<< orphan*/  spcr1; } ;
struct omap_mcbsp {unsigned int fmt; TYPE_1__* pdata; scalar_t__ configured; struct omap_mcbsp_reg_cfg cfg_regs; } ;
struct TYPE_2__ {scalar_t__ has_ccr; } ;

/* Variables and functions */
 int CLKRM ; 
 int CLKRP ; 
 int CLKXM ; 
 int CLKXP ; 
 int DXENDLY (int) ; 
 int EINVAL ; 
 int FREE ; 
 int /*<<< orphan*/  FSGM ; 
 int FSRM ; 
 int FSRP ; 
 int FSXM ; 
 int FSXP ; 
 int /*<<< orphan*/  RDATDLY (int) ; 
 int RDISABLE ; 
 int RDMAEN ; 
 int /*<<< orphan*/  RFIG ; 
 int RFULL_CYCLE ; 
 int /*<<< orphan*/  RINTM (int) ; 
 int /*<<< orphan*/  RJUST (int) ; 
#define  SND_SOC_DAIFMT_CBM_CFM 138 
#define  SND_SOC_DAIFMT_CBM_CFS 137 
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
 int /*<<< orphan*/  XDATDLY (int) ; 
 int XDISABLE ; 
 int XDMAEN ; 
 int /*<<< orphan*/  XFIG ; 
 int XINTM (int) ; 
 int /*<<< orphan*/  memset (struct omap_mcbsp_reg_cfg*,int /*<<< orphan*/ ,int) ; 
 struct omap_mcbsp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int omap_mcbsp_dai_set_dai_fmt(struct snd_soc_dai *cpu_dai,
				      unsigned int fmt)
{
	struct omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	struct omap_mcbsp_reg_cfg *regs = &mcbsp->cfg_regs;
	bool inv_fs = false;

	if (mcbsp->configured)
		return 0;

	mcbsp->fmt = fmt;
	memset(regs, 0, sizeof(*regs));
	/* Generic McBSP register settings */
	regs->spcr2	|= XINTM(3) | FREE;
	regs->spcr1	|= RINTM(3);
	/* RFIG and XFIG are not defined in 2430 and on OMAP3+ */
	if (!mcbsp->pdata->has_ccr) {
		regs->rcr2	|= RFIG;
		regs->xcr2	|= XFIG;
	}

	/* Configure XCCR/RCCR only for revisions which have ccr registers */
	if (mcbsp->pdata->has_ccr) {
		regs->xccr = DXENDLY(1) | XDMAEN | XDISABLE;
		regs->rccr = RFULL_CYCLE | RDMAEN | RDISABLE;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* 1-bit data delay */
		regs->rcr2	|= RDATDLY(1);
		regs->xcr2	|= XDATDLY(1);
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		/* 0-bit data delay */
		regs->rcr2	|= RDATDLY(0);
		regs->xcr2	|= XDATDLY(0);
		regs->spcr1	|= RJUST(2);
		/* Invert FS polarity configuration */
		inv_fs = true;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		/* 1-bit data delay */
		regs->rcr2      |= RDATDLY(1);
		regs->xcr2      |= XDATDLY(1);
		/* Invert FS polarity configuration */
		inv_fs = true;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		/* 0-bit data delay */
		regs->rcr2      |= RDATDLY(0);
		regs->xcr2      |= XDATDLY(0);
		/* Invert FS polarity configuration */
		inv_fs = true;
		break;
	default:
		/* Unsupported data format */
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		/* McBSP master. Set FS and bit clocks as outputs */
		regs->pcr0	|= FSXM | FSRM |
				   CLKXM | CLKRM;
		/* Sample rate generator drives the FS */
		regs->srgr2	|= FSGM;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		/* McBSP slave. FS clock as output */
		regs->srgr2	|= FSGM;
		regs->pcr0	|= FSXM | FSRM;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		/* McBSP slave */
		break;
	default:
		/* Unsupported master/slave configuration */
		return -EINVAL;
	}

	/* Set bit clock (CLKX/CLKR) and FS polarities */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/*
		 * Normal BCLK + FS.
		 * FS active low. TX data driven on falling edge of bit clock
		 * and RX data sampled on rising edge of bit clock.
		 */
		regs->pcr0	|= FSXP | FSRP |
				   CLKXP | CLKRP;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		regs->pcr0	|= CLKXP | CLKRP;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		regs->pcr0	|= FSXP | FSRP;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		break;
	default:
		return -EINVAL;
	}
	if (inv_fs == true)
		regs->pcr0 ^= FSXP | FSRP;

	return 0;
}
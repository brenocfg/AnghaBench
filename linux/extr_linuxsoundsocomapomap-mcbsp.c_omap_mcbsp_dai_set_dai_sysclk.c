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
struct omap_mcbsp_reg_cfg {int /*<<< orphan*/  pcr0; int /*<<< orphan*/  srgr2; } ;
struct omap_mcbsp {unsigned int in_freq; scalar_t__ active; struct omap_mcbsp_reg_cfg cfg_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKRM ; 
 int /*<<< orphan*/  CLKSM ; 
 int /*<<< orphan*/  CLKXM ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MCBSP_CLKS_PAD_SRC ; 
 int /*<<< orphan*/  MCBSP_CLKS_PRCM_SRC ; 
#define  OMAP_MCBSP_SYSCLK_CLK 132 
#define  OMAP_MCBSP_SYSCLK_CLKR_EXT 131 
#define  OMAP_MCBSP_SYSCLK_CLKS_EXT 130 
#define  OMAP_MCBSP_SYSCLK_CLKS_FCLK 129 
#define  OMAP_MCBSP_SYSCLK_CLKX_EXT 128 
 int /*<<< orphan*/  SCLKME ; 
 int /*<<< orphan*/  mcbsp_omap1 () ; 
 int omap2_mcbsp_set_clks_src (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 struct omap_mcbsp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int omap_mcbsp_dai_set_dai_sysclk(struct snd_soc_dai *cpu_dai,
					 int clk_id, unsigned int freq,
					 int dir)
{
	struct omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	struct omap_mcbsp_reg_cfg *regs = &mcbsp->cfg_regs;
	int err = 0;

	if (mcbsp->active) {
		if (freq == mcbsp->in_freq)
			return 0;
		else
			return -EBUSY;
	}

	mcbsp->in_freq = freq;
	regs->srgr2 &= ~CLKSM;
	regs->pcr0 &= ~SCLKME;

	switch (clk_id) {
	case OMAP_MCBSP_SYSCLK_CLK:
		regs->srgr2	|= CLKSM;
		break;
	case OMAP_MCBSP_SYSCLK_CLKS_FCLK:
		if (mcbsp_omap1()) {
			err = -EINVAL;
			break;
		}
		err = omap2_mcbsp_set_clks_src(mcbsp,
					       MCBSP_CLKS_PRCM_SRC);
		break;
	case OMAP_MCBSP_SYSCLK_CLKS_EXT:
		if (mcbsp_omap1()) {
			err = 0;
			break;
		}
		err = omap2_mcbsp_set_clks_src(mcbsp,
					       MCBSP_CLKS_PAD_SRC);
		break;

	case OMAP_MCBSP_SYSCLK_CLKX_EXT:
		regs->srgr2	|= CLKSM;
		regs->pcr0	|= SCLKME;
		/*
		 * If McBSP is master but yet the CLKX/CLKR pin drives the SRG,
		 * disable output on those pins. This enables to inject the
		 * reference clock through CLKX/CLKR. For this to work
		 * set_dai_sysclk() _needs_ to be called after set_dai_fmt().
		 */
		regs->pcr0	&= ~CLKXM;
		break;
	case OMAP_MCBSP_SYSCLK_CLKR_EXT:
		regs->pcr0	|= SCLKME;
		/* Disable ouput on CLKR pin in master mode */
		regs->pcr0	&= ~CLKRM;
		break;
	default:
		err = -ENODEV;
	}

	return err;
}
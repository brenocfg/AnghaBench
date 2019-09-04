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
typedef  int u32 ;
struct fsl_ssi_regvals {int srcr; int stcr; int sier; int scr; } ;
struct fsl_ssi {int /*<<< orphan*/  streams; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; scalar_t__ use_dma; TYPE_1__* soc; struct fsl_ssi_regvals* regvals; } ;
struct TYPE_2__ {scalar_t__ offline_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  REG_SSI_SCR ; 
 int /*<<< orphan*/  REG_SSI_SFCSR ; 
 int /*<<< orphan*/  REG_SSI_SIER ; 
 int /*<<< orphan*/  REG_SSI_SOR ; 
 int /*<<< orphan*/  REG_SSI_SRCR ; 
 int /*<<< orphan*/  REG_SSI_STCR ; 
 size_t RX ; 
 int SSI_SCR_SSIEN ; 
 scalar_t__ SSI_SFCSR_TFCNT0 (int) ; 
 int SSI_SOR_xX_CLR (int) ; 
 size_t TX ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void fsl_ssi_config_enable(struct fsl_ssi *ssi, bool tx)
{
	struct fsl_ssi_regvals *vals = ssi->regvals;
	int dir = tx ? TX : RX;
	u32 sier, srcr, stcr;

	/* Clear dirty data in the FIFO; It also prevents channel slipping */
	regmap_update_bits(ssi->regs, REG_SSI_SOR,
			   SSI_SOR_xX_CLR(tx), SSI_SOR_xX_CLR(tx));

	/*
	 * On offline_config SoCs, SxCR and SIER are already configured when
	 * the previous stream started. So skip all SxCR and SIER settings
	 * to prevent online reconfigurations, then jump to set SCR directly
	 */
	if (ssi->soc->offline_config && ssi->streams)
		goto enable_scr;

	if (ssi->soc->offline_config) {
		/*
		 * Online reconfiguration not supported, so enable all bits for
		 * both streams at once to avoid necessity of reconfigurations
		 */
		srcr = vals[RX].srcr | vals[TX].srcr;
		stcr = vals[RX].stcr | vals[TX].stcr;
		sier = vals[RX].sier | vals[TX].sier;
	} else {
		/* Otherwise, only set bits for the current stream */
		srcr = vals[dir].srcr;
		stcr = vals[dir].stcr;
		sier = vals[dir].sier;
	}

	/* Configure SRCR, STCR and SIER at once */
	regmap_update_bits(ssi->regs, REG_SSI_SRCR, srcr, srcr);
	regmap_update_bits(ssi->regs, REG_SSI_STCR, stcr, stcr);
	regmap_update_bits(ssi->regs, REG_SSI_SIER, sier, sier);

enable_scr:
	/*
	 * Start DMA before setting TE to avoid FIFO underrun
	 * which may cause a channel slip or a channel swap
	 *
	 * TODO: FIQ cases might also need this upon testing
	 */
	if (ssi->use_dma && tx) {
		int try = 100;
		u32 sfcsr;

		/* Enable SSI first to send TX DMA request */
		regmap_update_bits(ssi->regs, REG_SSI_SCR,
				   SSI_SCR_SSIEN, SSI_SCR_SSIEN);

		/* Busy wait until TX FIFO not empty -- DMA working */
		do {
			regmap_read(ssi->regs, REG_SSI_SFCSR, &sfcsr);
			if (SSI_SFCSR_TFCNT0(sfcsr))
				break;
		} while (--try);

		/* FIFO still empty -- something might be wrong */
		if (!SSI_SFCSR_TFCNT0(sfcsr))
			dev_warn(ssi->dev, "Timeout waiting TX FIFO filling\n");
	}
	/* Enable all remaining bits in SCR */
	regmap_update_bits(ssi->regs, REG_SSI_SCR,
			   vals[dir].scr, vals[dir].scr);

	/* Log the enabled stream to the mask */
	ssi->streams |= BIT(dir);
}
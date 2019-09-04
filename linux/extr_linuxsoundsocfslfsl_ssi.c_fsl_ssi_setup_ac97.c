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
struct regmap {int dummy; } ;
struct fsl_ssi {struct regmap* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SSI_SACNT ; 
 int /*<<< orphan*/  REG_SSI_SCR ; 
 int /*<<< orphan*/  REG_SSI_SOR ; 
 int /*<<< orphan*/  REG_SSI_SRCCR ; 
 int /*<<< orphan*/  REG_SSI_STCCR ; 
 int SSI_SACNT_AC97EN ; 
 int SSI_SACNT_FV ; 
 int SSI_SCR_RE ; 
 int SSI_SCR_SSIEN ; 
 int SSI_SCR_TE ; 
 int SSI_SOR_WAIT (int) ; 
 int SSI_SxCCR_DC (int) ; 
 int SSI_SxCCR_WL (int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fsl_ssi_setup_ac97(struct fsl_ssi *ssi)
{
	struct regmap *regs = ssi->regs;

	/* Setup the clock control register */
	regmap_write(regs, REG_SSI_STCCR, SSI_SxCCR_WL(17) | SSI_SxCCR_DC(13));
	regmap_write(regs, REG_SSI_SRCCR, SSI_SxCCR_WL(17) | SSI_SxCCR_DC(13));

	/* Enable AC97 mode and startup the SSI */
	regmap_write(regs, REG_SSI_SACNT, SSI_SACNT_AC97EN | SSI_SACNT_FV);

	/* AC97 has to communicate with codec before starting a stream */
	regmap_update_bits(regs, REG_SSI_SCR,
			   SSI_SCR_SSIEN | SSI_SCR_TE | SSI_SCR_RE,
			   SSI_SCR_SSIEN | SSI_SCR_TE | SSI_SCR_RE);

	regmap_write(regs, REG_SSI_SOR, SSI_SOR_WAIT(3));
}
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
typedef  int /*<<< orphan*/  u32 ;
struct fsl_ssi {int /*<<< orphan*/  dai_fmt; int /*<<< orphan*/  regs; scalar_t__ use_dual_fifo; int /*<<< orphan*/  fifo_watermark; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SSI_SCR ; 
 int /*<<< orphan*/  REG_SSI_SFCSR ; 
 int /*<<< orphan*/  SSI_SCR_TCH_EN ; 
 int SSI_SFCSR_RFWM0 (int /*<<< orphan*/ ) ; 
 int SSI_SFCSR_RFWM1 (int /*<<< orphan*/ ) ; 
 int SSI_SFCSR_TFWM0 (int /*<<< orphan*/ ) ; 
 int SSI_SFCSR_TFWM1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fsl_ssi_set_dai_fmt (struct fsl_ssi*,int /*<<< orphan*/ ) ; 
 scalar_t__ fsl_ssi_is_ac97 (struct fsl_ssi*) ; 
 int /*<<< orphan*/  fsl_ssi_setup_ac97 (struct fsl_ssi*) ; 
 int /*<<< orphan*/  fsl_ssi_setup_regvals (struct fsl_ssi*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsl_ssi_hw_init(struct fsl_ssi *ssi)
{
	u32 wm = ssi->fifo_watermark;

	/* Initialize regvals */
	fsl_ssi_setup_regvals(ssi);

	/* Set watermarks */
	regmap_write(ssi->regs, REG_SSI_SFCSR,
		     SSI_SFCSR_TFWM0(wm) | SSI_SFCSR_RFWM0(wm) |
		     SSI_SFCSR_TFWM1(wm) | SSI_SFCSR_RFWM1(wm));

	/* Enable Dual FIFO mode */
	if (ssi->use_dual_fifo)
		regmap_update_bits(ssi->regs, REG_SSI_SCR,
				   SSI_SCR_TCH_EN, SSI_SCR_TCH_EN);

	/* AC97 should start earlier to communicate with CODECs */
	if (fsl_ssi_is_ac97(ssi)) {
		_fsl_ssi_set_dai_fmt(ssi, ssi->dai_fmt);
		fsl_ssi_setup_ac97(ssi);
	}

	return 0;
}
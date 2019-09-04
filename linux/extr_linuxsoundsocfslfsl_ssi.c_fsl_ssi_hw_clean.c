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
struct fsl_ssi {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SSI_SACNT ; 
 int /*<<< orphan*/  REG_SSI_SCR ; 
 int /*<<< orphan*/  REG_SSI_SOR ; 
 int SSI_SCR_RE ; 
 int SSI_SCR_SSIEN ; 
 int SSI_SCR_TE ; 
 scalar_t__ fsl_ssi_is_ac97 (struct fsl_ssi*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_ssi_hw_clean(struct fsl_ssi *ssi)
{
	/* Disable registers for AC97 */
	if (fsl_ssi_is_ac97(ssi)) {
		/* Disable TE and RE bits first */
		regmap_update_bits(ssi->regs, REG_SSI_SCR,
				   SSI_SCR_TE | SSI_SCR_RE, 0);
		/* Disable AC97 mode */
		regmap_write(ssi->regs, REG_SSI_SACNT, 0);
		/* Unset WAIT bits */
		regmap_write(ssi->regs, REG_SSI_SOR, 0);
		/* Disable SSI -- software reset */
		regmap_update_bits(ssi->regs, REG_SSI_SCR, SSI_SCR_SSIEN, 0);
	}
}
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
struct fsl_asrc {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ASRCTR_ASRCEN ; 
 int /*<<< orphan*/  ASRTFR1_TF_BASE (int) ; 
 int /*<<< orphan*/  ASRTFR1_TF_BASE_MASK ; 
 int /*<<< orphan*/  REG_ASR56K ; 
 int /*<<< orphan*/  REG_ASR76K ; 
 int /*<<< orphan*/  REG_ASRCTR ; 
 int /*<<< orphan*/  REG_ASRIER ; 
 int /*<<< orphan*/  REG_ASRPM1 ; 
 int /*<<< orphan*/  REG_ASRPM2 ; 
 int /*<<< orphan*/  REG_ASRPM3 ; 
 int /*<<< orphan*/  REG_ASRPM4 ; 
 int /*<<< orphan*/  REG_ASRPM5 ; 
 int /*<<< orphan*/  REG_ASRTFR1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsl_asrc_init(struct fsl_asrc *asrc_priv)
{
	/* Halt ASRC internal FP when input FIFO needs data for pair A, B, C */
	regmap_write(asrc_priv->regmap, REG_ASRCTR, ASRCTR_ASRCEN);

	/* Disable interrupt by default */
	regmap_write(asrc_priv->regmap, REG_ASRIER, 0x0);

	/* Apply recommended settings for parameters from Reference Manual */
	regmap_write(asrc_priv->regmap, REG_ASRPM1, 0x7fffff);
	regmap_write(asrc_priv->regmap, REG_ASRPM2, 0x255555);
	regmap_write(asrc_priv->regmap, REG_ASRPM3, 0xff7280);
	regmap_write(asrc_priv->regmap, REG_ASRPM4, 0xff7280);
	regmap_write(asrc_priv->regmap, REG_ASRPM5, 0xff7280);

	/* Base address for task queue FIFO. Set to 0x7C */
	regmap_update_bits(asrc_priv->regmap, REG_ASRTFR1,
			   ASRTFR1_TF_BASE_MASK, ASRTFR1_TF_BASE(0xfc));

	/* Set the processing clock for 76KHz to 133M */
	regmap_write(asrc_priv->regmap, REG_ASR76K, 0x06D6);

	/* Set the processing clock for 56KHz to 133M */
	return regmap_write(asrc_priv->regmap, REG_ASR56K, 0x0947);
}
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
struct fsl_asrc_pair {int index; int channels; struct fsl_asrc* asrc_priv; } ;
struct fsl_asrc {int /*<<< orphan*/  regmap; } ;
typedef  enum asrc_pair_index { ____Placeholder_asrc_pair_index } asrc_pair_index ;

/* Variables and functions */
 int ASRCFG_INIRQi_MASK (int) ; 
 int /*<<< orphan*/  ASRCTR_ASRCE (int) ; 
 int /*<<< orphan*/  ASRCTR_ASRCEi_MASK (int) ; 
 int /*<<< orphan*/  ASRIER_AOLIE ; 
 int /*<<< orphan*/  REG_ASRCFG ; 
 int /*<<< orphan*/  REG_ASRCNCR ; 
 int /*<<< orphan*/  REG_ASRCTR ; 
 int /*<<< orphan*/  REG_ASRDI (int) ; 
 int /*<<< orphan*/  REG_ASRIER ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void fsl_asrc_start_pair(struct fsl_asrc_pair *pair)
{
	struct fsl_asrc *asrc_priv = pair->asrc_priv;
	enum asrc_pair_index index = pair->index;
	int reg, retry = 10, i;

	/* Enable the current pair */
	regmap_update_bits(asrc_priv->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_MASK(index), ASRCTR_ASRCE(index));

	/* Wait for status of initialization */
	do {
		udelay(5);
		regmap_read(asrc_priv->regmap, REG_ASRCFG, &reg);
		reg &= ASRCFG_INIRQi_MASK(index);
	} while (!reg && --retry);

	/* Make the input fifo to ASRC STALL level */
	regmap_read(asrc_priv->regmap, REG_ASRCNCR, &reg);
	for (i = 0; i < pair->channels * 4; i++)
		regmap_write(asrc_priv->regmap, REG_ASRDI(index), 0);

	/* Enable overload interrupt */
	regmap_write(asrc_priv->regmap, REG_ASRIER, ASRIER_AOLIE);
}
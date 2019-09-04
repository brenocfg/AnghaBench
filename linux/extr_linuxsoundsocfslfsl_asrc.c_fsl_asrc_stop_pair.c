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
struct fsl_asrc_pair {int index; struct fsl_asrc* asrc_priv; } ;
struct fsl_asrc {int /*<<< orphan*/  regmap; } ;
typedef  enum asrc_pair_index { ____Placeholder_asrc_pair_index } asrc_pair_index ;

/* Variables and functions */
 int /*<<< orphan*/  ASRCTR_ASRCEi_MASK (int) ; 
 int /*<<< orphan*/  REG_ASRCTR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_asrc_stop_pair(struct fsl_asrc_pair *pair)
{
	struct fsl_asrc *asrc_priv = pair->asrc_priv;
	enum asrc_pair_index index = pair->index;

	/* Stop the current pair */
	regmap_update_bits(asrc_priv->regmap, REG_ASRCTR,
			   ASRCTR_ASRCEi_MASK(index), 0);
}
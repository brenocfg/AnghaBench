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
 int EINVAL ; 
 int IDEAL_RATIO_DECIMAL_DEPTH ; 
 int /*<<< orphan*/  REG_ASRIDRH (int) ; 
 int /*<<< orphan*/  REG_ASRIDRL (int) ; 
 int /*<<< orphan*/  pair_err (char*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int fsl_asrc_set_ideal_ratio(struct fsl_asrc_pair *pair,
				    int inrate, int outrate)
{
	struct fsl_asrc *asrc_priv = pair->asrc_priv;
	enum asrc_pair_index index = pair->index;
	unsigned long ratio;
	int i;

	if (!outrate) {
		pair_err("output rate should not be zero\n");
		return -EINVAL;
	}

	/* Calculate the intergal part of the ratio */
	ratio = (inrate / outrate) << IDEAL_RATIO_DECIMAL_DEPTH;

	/* ... and then the 26 depth decimal part */
	inrate %= outrate;

	for (i = 1; i <= IDEAL_RATIO_DECIMAL_DEPTH; i++) {
		inrate <<= 1;

		if (inrate < outrate)
			continue;

		ratio |= 1 << (IDEAL_RATIO_DECIMAL_DEPTH - i);
		inrate -= outrate;

		if (!inrate)
			break;
	}

	regmap_write(asrc_priv->regmap, REG_ASRIDRL(index), ratio);
	regmap_write(asrc_priv->regmap, REG_ASRIDRH(index), ratio >> 24);

	return 0;
}